#include "most_active_cookie.h"
#include "unit_test_framework.h" //pre built framework
#include <iostream>
#include <string>

using namespace std;

TEST(test_convert_date)
{
    mostActiveCookies test;

    string date = "1530-32-23";

    ASSERT_EQUAL(test.convertDate("1530-32-23"), 15303223);
}

TEST_MAIN()