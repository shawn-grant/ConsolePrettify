/*
    MIT License

    Copyright (c) 2020 Shawn Grant

    Permission is hereby granted, free of charge, to any person obtaining a copy
    of this software and associated documentation files (the "Software"), to deal
    in the Software without restriction, including without limitation the rights
    to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
    copies of the Software, and to permit persons to whom the Software is
    furnished to do so, subject to the following conditions:

    The above copyright notice and this permission notice shall be included in all
    copies or substantial portions of the Software.
*/

/*
  Programmer    : Shawn Grant
  Date Created  : 13, 09, 2020
  Purpose	    : To mimic GUI elements with text in a console environment
*/

#include "ConsolePrettify.h"

int CUR_COLOR = WHITE;

// CHANGES TEXT COLOR
void prettify_textcolor(int COLOR){
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), COLOR);
    CUR_COLOR = COLOR;
}

/// CREATE A NON CENTERED INPUT FIELD
/// EX. prettify_textbox("%s", &myvariable, BLUE);
void prettify_textbox(char specifier[], void *var, int COLOR)
{
    COORD coord;//where to put the cursor
    CONSOLE_SCREEN_BUFFER_INFO cursor;//the cursor
    int returnColor = CUR_COLOR;

    if(COLOR != NULL)
        prettify_textcolor(COLOR);

    printf("\n");

    printf ("  _____________________________\n");
    printf (" |                             |\n");
    printf (" |_____________________________|\n");

    if(strcmp(specifier, "%s") == 0)
        printf ("             (text)             ");
    else if (strcmp(specifier, "%c") == 0)
        printf ("            (character)         ");
    else
        printf ("            (number)            ");


    ///positioning the cursor inside the box
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor);

    coord.X = cursor.dwCursorPosition.X - 29;
    coord.Y = cursor.dwCursorPosition.Y - 2;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);

    ///reading the variable
    if(strcmp(specifier, "%s") != 0) //not a string
    {
        scanf(specifier, var);
    }
    else//is a string
    {
        gets(var);
    }

    //return to previous text color
    prettify_textcolor(returnColor);

    ///re-place the cursor outside the box
    coord.Y += 3;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
    printf("\n");
}


/// CREATE A NON CENTERED INPUT FIELD FOR PASSWORDS OR SECRET CODES
/// EX. prettify_textbox_password(password, '*', BLUE);
void prettify_textbox_password(char *var, char occluder, int COLOR)
{
    COORD coord;//where to put the cursor
    CONSOLE_SCREEN_BUFFER_INFO cursor;//the cursor
    int returnColor = CUR_COLOR;
    char c, password[25] = "";
    int i = 0;

    if(COLOR != NULL)
        prettify_textcolor(COLOR);

    printf("\n");

    printf ("  _____________________________\n");
    printf (" |                             |\n");
    printf (" |_____________________________|\n");
    printf ("             (text)             ");

    ///positioning the cursor inside the box
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor);

    coord.X = cursor.dwCursorPosition.X - 29;
    coord.Y = cursor.dwCursorPosition.Y - 2;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);

    ///reading the password
    while((c = getch()) != '\r')//return or enter key
    {
        if(c == '\b')//backspace pressed
        {
            ///manually remove perform backspace action
            if(strlen(password) > 0)
            {
                password[strlen(password)-1] = '\0';//remove last character
                printf("\b \b");//visual backspace
                i--;
            }
        }
        else
        {
            ///check to ensure its a letter or number and not an arrow
            ///because getch seems to accept EVERYTHING on the keyboard as a char
            if((isalpha(c) != 0 || isdigit(c) == 1) && (c != 72 && c != 80 && c != 75 && c != 77))
            {
                password[i] = c;
                printf("%c",occluder);
                i++;
            }
        }
    }

    password[i] = '\0';//end the string
    strcpy(var, password);

    //return to previous text color
    prettify_textcolor(returnColor);

    ///re-place the cursor outside the box
    coord.Y += 3;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
    printf("\n");
}


//DISPLAYS A TABLE FOR YOU
/// EX. prettify_table(listOfHeadings, numRows, listOfNames, listOfAges);
void prettify_table(char *headings, int rows, int COLOR, ...)
{
   va_list args;
   va_start(args, COLOR);
   int returnColor = CUR_COLOR;

   prettify_textcolor(COLOR);

   va_arg(args, int);

   va_end(args);
   prettify_textcolor(returnColor);
}


//DISPLAYS A MENU AND RETURNS THE NUMBER OF THE SELECTED OPTION
/// EX. prettify_menu("Select an option", numOptions, RED, "Buy banana","Buy apple","Buy mango");
int prettify_menu(char *title, int COLOR, int numOptions, ...)
{
    int i, j, result;
    int returnColor = CUR_COLOR;
    int maxLength = strlen(title);
    va_list args;
    COORD coord;//where to put the cursor
    CONSOLE_SCREEN_BUFFER_INFO cursor;//the cursor

    va_start(args, numOptions);
    prettify_textcolor(COLOR);

    //find the longest text to be displayed
    for (i = 0; i < numOptions; i++)
    {
        int len = strlen(va_arg(args, char *));
        if(len > maxLength)
            maxLength = len;
    }

    printf("\n  ");
    for (i = 0; i < maxLength + 6; i++)
        printf("_");

    printf("\n | %s", title);
    for (i = 0; i < maxLength - (strlen(title)- 5); i++)
        printf(" ");

    printf("|\n |");
    for (i = 0; i < maxLength + 6; i++)
        printf("-");
    printf("|");

    va_start(args, numOptions);
    for (i = 0; i < numOptions; i++)
    {
        char *option = va_arg(args, char *);

        printf("\n | %i) %s", i+1, option);
        for (j = 0; j < maxLength - (strlen(option)-2); j++)
            printf(" ");
        printf("|");
    }

    printf("\n |");
    for (i = 0; i < maxLength + 6; i++)
        printf("_");
    printf("|");

    //text box
    printf("\n | > ");
    for (i = 0; i < maxLength + 3; i++)
        printf(" ");

    printf("|\n |");
    for (i = 0; i < maxLength + 6; i++)
        printf("_");
    printf("|");

    va_end(args);
    prettify_textcolor(returnColor);

    //put cursor inside box
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor);
    coord.X = cursor.dwCursorPosition.X - (maxLength + 4);
    coord.Y = cursor.dwCursorPosition.Y - 1;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);

    int c = scanf("%i", &result);

    ///re-place the cursor outside the box
    coord.X = 0;
    coord.Y += 2;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);

    //error checking
    if(c == 1 && result <= numOptions && result > 0){
        return result;
    }
    else{
        //prettify_textcolor(RED);
        printf("\n --> ERROR: INVALID OPTION\n Try again..");
        return 0;
    }
}


//DISPLAYS AN ORDERED LIST
/// EX. prettify_list_ordered("Select an option", RED, items);
void prettify_list_ordered(char *heading, int COLOR, int items[])
{
    int i, j, numDigits, curNumDigits, numItems = 0;
    int returnColor = CUR_COLOR;

    prettify_textcolor(COLOR);

    //get number of items
    while(items[numItems] != NULL)
        numItems++;

    numDigits = (numItems == 0) ? 1  : (log10(numItems) + 1);

    printf("\n\n  %s\n", heading);
    //printf("  ________________________\n");

    for(i = 0; i < numItems; i++)
    {
        curNumDigits = (i+1 == 0) ? 1  : (log10(i+1) + 1);
        printf("   %i", i+1);

        for(j = 0; j < numDigits-curNumDigits; j++)
            printf(" ");

        printf("- %i\n", items[i]);
    }

    prettify_textcolor(returnColor);
}

void prettify_profile_icon()
{

}

void prettify_print(char str[], int COLOR)
{
    COORD centerPos;
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    int screenWwidth;
    int returnColor = CUR_COLOR;

    prettify_textcolor(COLOR);

    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    screenWwidth = csbi.srWindow.Right - csbi.srWindow.Left + 1;

    /// cursor to center
    centerPos.X = (screenWwidth - strlen(str)) / 2;
    centerPos.Y = csbi.dwCursorPosition.Y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), centerPos);
    /// print
    printf(str);

    prettify_textcolor(returnColor);
}
