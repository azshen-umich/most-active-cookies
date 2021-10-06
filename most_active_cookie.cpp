#include <iostream>
#include <utility>
#include <vector>
#include <algorithm>
#include <getopt.h>
#include <string>
#include <fstream>
#include "mostActiveCookies.h"
#include <unordered_map>

using namespace std;

class mostActiveCookies
{
public:
    struct CookieInfo
    {
        string cookie;   //string of the cookie from the log
        int cookieCount; //number of cookies that appear on specific date

        CookieInfo(string cookies, int numCookie) : cookie(cookies), cookieCount(numCookie) {}
    };
    //functor to compare which cookies have higher counts
    struct compareCookies
    {
        bool operator()(const CookieInfo cookie1, const CookieInfo cookie2)
        {
            return cookie1.cookieCount > cookie2.cookieCount;
        }
    };
    //reads in command line arguments
    void readCmdLine(int argc, char *argv[]);
    //finds most active cookies from given day
    void findActiveCookie();
    //removes the dashes in the date and coverts it to a string to int
    int convertDate(string stringDate);
    //read the cookie log and initialize data structures with the log info
    void readLog();

private:
    bool utc = false;                           // -d utc time zone parameter
    int dateIn;                                 //the specified date from command line
    unordered_map<int, vector<CookieInfo>> map; //key value pair with date and list of cookies on that date
    ifstream infile;                            //cookie logfile
};

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

        if (map.find(date) == map.end()) //check if date key exists, add cookie to that date
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