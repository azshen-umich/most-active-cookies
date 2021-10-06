#include <iostream>
#include <utility>
#include <vector>
#include <algorithm>
#include <getopt.h>
#include <string>
#include <fstream>
#include "most_active_cookie.h"
#include <unordered_map>

using namespace std;

void mostActiveCookies::readCmdLine(int argc, char *argv[])
{
    infile.open(argv[1]);
    streambuf *cinbuf = cin.rdbuf();
    cin.rdbuf(infile.rdbuf());

    if (argv[2] == "-d")
    {
        utc = true;
    }
    dateIn = convertDate(argv[3]);
}

int mostActiveCookies::convertDate(string stringDate)
{
    if (stringDate.length() == 10) //check if the stringDate is from command line
    {
        //remove the dashes from the date
        stringDate.erase(stringDate.begin() + 4);
        stringDate.erase(stringDate.begin() + 6);
    }
    //convert to integer
    return stoi(stringDate);
}

void mostActiveCookies::readLog()
{
    string cookieInput, dateInput, trash, input;
    int date, time;

    getline(cin, trash); //throw out first line

    while (cin >> input)
    {
        cookieInput = input.substr(0, input.find(","));
        dateInput = input.substr(input.find(",") + 1, input.length());

        dateInput.erase(dateInput.begin() + 4);
        dateInput.erase(dateInput.begin() + 6);
        dateInput.erase(dateInput.begin() + 8, dateInput.end());
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
            else //if cookie DNE, add it
            {
                map[date].push_back(CookieInfo(cookieInput, 1));
            }
        }
        else //if date key DNE, then insert a new key value pair.
        {
            map[date].push_back(CookieInfo(cookieInput, 1));
        }
    }
    infile.close();
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

int main(int argc, char *argv[])
{
    mostActiveCookies cookie;
    cookie.readCmdLine(argc, argv);
    cookie.readLog();
    cookie.findActiveCookie();
    exit(0);
}