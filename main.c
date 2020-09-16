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
    */

    choice = prettify_menu("Select an option", 4, RED,
                  "Buy bananas",
                  "Buy apple",
                  "Buy mango",
                  "Buy grapes");

    return 0;
}
