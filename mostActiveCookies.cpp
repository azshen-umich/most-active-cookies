#include <iostream>
#include <vector>
#include <algorithm>
#include <getopt.h>
#include <string>
#include "mostActiveCookies.h"

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
}
