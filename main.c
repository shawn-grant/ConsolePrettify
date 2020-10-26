/*
  Programmer    : Shawn Grant
  Date Created  : 13, 09, 2020
  Purpose	    : To show off/test ConsolePrettify functions
*/

#include <stdio.h>
#include <stdlib.h>
#include "ConsolePrettify.h"

int main()
{
    int num, choice;
    char pass[25];

    /*
    printf("THIS IS A PRETTIFY TEXTBOX");
    prettify_textbox("%i", &num, YELLOW);
    printf("You Entered: %i", num);

    printf("\n\nTHIS IS A PRETTIFY PASSWORD BOX");
    prettify_textbox_password(pass, '+', BLUE);
    printf("You Entered: %s", pass);


    choice = prettify_menu("Select an option", RED, 4,
                  "Buy bananas",
                  "Buy apple",
                  "Buy mango",
                  "Buy grapes");
    */

    prettify_print("HELLO\n ui", RED);

    /*if(prettify_menu("Select an option", RED, 4,
                  "Buy bananas",
                  "Buy apple",
                  "Buy mango",
                  "Buy grapes") == 3)
                  printf("Help\n");
    */


    float items[20] = {20.890, 10.8, 80, 900, 20, 10, 80, 900, 209, 50};
    prettify_olist_f("List of numbers", YELLOW, items);

    //char people[20][20] = {"Justin", "Kim", "Susan"};
    //prettify_list_ordered("List of People", GREEN, "%s", people);

    return 0;
}
