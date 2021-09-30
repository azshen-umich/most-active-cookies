#include <iostream>
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
    exit(0);
}

void mostActiveCookies::readCmdLine(int argc, char *argv[])
{
    filename = argv[0];
    if (argv[1] == "-d")
    {
        utc = true;
    }
    date = convertDate(argv[2]);
}

int convertDate(string stringDate)
{
    //remove the dashes from the date
    stringDate.erase(stringDate.begin() + 4);
    stringDate.erase(stringDate.begin() + 7);

    //convert to integer
    return stoi(stringDate);
}
