#include <iostream>
#include <vector>
#include <algorithm>
#include <getopt.h>
#include <string>
#include <unordered_map>

using namespace std;

class mostActiveCookies
{
public:
    //reads in command line arguments
    void readCmdLine(int argc, char *argv[]);
    //finds most active cookies from given day
    void findActiveCookie();
    //removes the dashes in the date and coverts it to a string to int
    int convertDate(string stringDate);

private:
    string filename;  //name of the cookies log file
    bool utc = false; // -d utc time zone parameter
    int date;         //the specified date from command line
};