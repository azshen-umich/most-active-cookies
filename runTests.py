#script to run all the tests
import os
import sys
from subprocess import run



def main():
    if os.system("g++ most_active_cookie.cpp -o most_active_cookie") != 0:
        print("error")
        exit()


    output = os.system("./most_active_cookie cookie_log1.csv -d 2018-12-08")
    print (output)


if __name__ == "__main__":
    main()