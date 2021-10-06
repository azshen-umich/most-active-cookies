#include <iostream>
#include <vector>
#include <algorithm>
#include <getopt.h>
#include <string>
#include <unordered_map>
#include <map>
#include <queue>
#include <fstream>

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