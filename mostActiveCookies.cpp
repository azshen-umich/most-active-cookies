#include <iostream>
#include <utility>
#include <vector>
#include <algorithm>
#include <getopt.h>
#include <string>
#include "mostActiveCookies.h"
#include <unordered_map>

using namespace std;

int main(int argc, char *argv[])
{
    mostActiveCookies cookie;
    cookie.readCmdLine(argc, argv);
    cookie.readLog();
    cookie.findActiveCookie();
    exit(0);
}

void mostActiveCookies::readCmdLine(int argc, char *argv[])
{
    filename = argv[0];
    if (argv[1] == "-d")
    {
        utc = true;
    }
    dateIn = convertDate(argv[2]);
}

int mostActiveCookies::convertDate(string stringDate)
{
    cout << stringDate;
    if (stringDate.length() == 10) //check if the stringDate is from command line
    {
        //remove the dashes from the date
        stringDate.erase(stringDate.begin() + 4);
        stringDate.erase(stringDate.begin() + 7);
    }
    //convert to integer
    return stoi(stringDate);
}

void mostActiveCookies::readLog()
{
    string cookieInput, dateInput, trash;
    int date, time;

    getline(cin, trash); //throw out first line

    while (cin >> cookieInput)
    {
        cin >> dateInput;

        dateInput.erase(dateInput.begin() + 4);
        dateInput.erase(dateInput.begin() + 7);
        dateInput.erase(dateInput.begin() + 10, dateInput.end());
        date = stoi(dateInput);

        pair<int, vector<CookieInfo>> temp;

        if (map.find(date) != map.end()) //check if date key exists, add cookie to that date
        {
            auto pred = [cookieInput](CookieInfo cookieData)
            {
                return cookieData.cookie == cookieInput;
            };

            if (find_if(map[date].begin(), map[date].end(), pred) != map[date].end()) //check if cookie exists, if does increment the count
            {
                auto it = find_if(map[date].begin(), map[date].end(), pred);
                it->cookieCount++;
            }
            else
            {
                map[date].push_back(CookieInfo(cookieInput, 1));
            }
        }
        else //if date key DNE, then insert a new key value pair.
        {
            temp.first = date;
            temp.second.push_back(CookieInfo(cookieInput, 1));
        }
    }
}

void mostActiveCookies::findActiveCookie()
{
    sort(map[dateIn].begin(), map[dateIn].end(), compareCookies()); //sort the cookies by count on the input date

    const int countHighest = map[dateIn][0].cookieCount; //save the most active

    for (size_t i = 0; i < map[dateIn].size(); i++) //check if there are any other cookies with equal counts
    {
        if (map[dateIn][i].cookieCount == countHighest)
        {
            cout << map[dateIn][i].cookie << endl;
        }
        else
        {
            return;
        }
    }
}
