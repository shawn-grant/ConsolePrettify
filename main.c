/*
  Programmer    : Shawn Grant
  Date Created  : 13, 09, 2020
  Purpose	    : To show off/test ConsolePrettify functions
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "ConsolePrettify.h"

int main()
{
    char testString[25];

    cp_textcolor (GREEN); //change color
    cp_print("\b HELLO TO %s", "CONSOLE PRETTIFY");

    cp_menu2("Select an option", 5,
                  "Buy bananas",
                  "Buy apple",
                  "Buy mango",
                  "Buy grapes",
                  "Buy Bananas");

    cp_textcolor(BLUE);


    printf (" Enter your username");
    cp_textbox ("%s", testString);

    printf (" Enter your password:");
    cp_password (testString);

    ////////////////////////////////
    /*float items[20] = {200, 10, 80, 900, 20, 10, 80, 900, 209, 50};
    cp_flist("List of numbers", items, 10);

    char chars[5] = "HELLO";
    cp_clist("List of Chars", chars, 5);

    char people[20][20] = {"Justin", "Kim", "Susan"};
    cp_slist("List of People", people, 3);

    cp_table("Table");*/

    return 0;
}
