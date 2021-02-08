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

void error(char function[25], char msg[100])
{
    printf ("\n!!!!ERROR: In function '%s' !!!!\n %s\n", function, msg);
    exit(EXIT_FAILURE);
}

void cp_setCentered(int isCentered)
{

}

// CHANGES TEXT COLOR
void cp_textcolor(int COLOR){
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), COLOR);
}

/// CREATE A NON CENTERED INPUT FIELD
/// EX. cp_textbox("%s", &myvariable);
void cp_textbox(char *specifier, void *var)
{
    COORD coord;//where to put the cursor
    CONSOLE_SCREEN_BUFFER_INFO cursor;//the cursor
    fflush(stdin);

    printf ("\n  _____________________________");
    printf ("\n |                             |");
    printf ("\n |_____________________________|");

    if(strcmp(specifier, "%s") == 0)
        printf ("\n                          [text]\n");
    else if (strcmp(specifier, "%c") == 0)
        printf ("\n                     [character]\n");
    else
        printf ("\n                        [number]\n");

    ///positioning the cursor inside the box
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor);

    coord.X = 4;
    coord.Y = cursor.dwCursorPosition.Y - 3;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);

    ///reading the variable
    if (strcmp(specifier, "%s") != 0) //not a string
    {
        scanf (specifier, var);
    }
    else//is a string
    {
        gets(var);
    }

    ///re-place the cursor outside the box
    coord.Y += 3;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
    printf("\n");
}


/// CREATE A NON CENTERED INPUT FIELD FOR PASSWORDS OR SECRET CODES
/// EX. cp_password(password);
void cp_password(char *var)
{
    COORD coord;//where to put the cursor
    CONSOLE_SCREEN_BUFFER_INFO cursor;//the cursor
    char c, password[25] = "";
    int i = 0;

    printf ("\n  _____________________________");
    printf ("\n |                             |");
    printf ("\n |_____________________________|");
    printf ("\n                          [text]\n");

    ///positioning the cursor inside the box
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor);

    coord.X = 4;
    coord.Y = cursor.dwCursorPosition.Y - 3;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);

    ///reading the password
    while((c = getch()) != '\r')//return or enter key
    {
        fflush(stdin);
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
                printf("%c", '*');
                i++;
            }
        }
    }

    password[i] = '\0';//end the string
    strcpy(var, password);

    ///re-place the cursor outside the box
    coord.Y += 3;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
    printf("\n");
}

//DISPLAYS A MENU AND RETURNS THE NUMBER OF THE SELECTED OPTION
/// EX. cp_menu("Select an option", 4, "Buy banana","Buy apple","Buy mango");
int cp_menu(char *title, int numOptions, ...)
{
    int i, result;
    int maxLength = strlen(title);
    //if its the 20th option thn, then digitsInOption will be 2
    int digitsInOption;
    va_list args;
    COORD coord;//where to put the cursor
    CONSOLE_SCREEN_BUFFER_INFO cursor;//the cursor
    fflush(stdin);

    va_start(args, numOptions);

    //find the longest text to be displayed
    for (i = 0; i < numOptions; i++)
    {
        int len = strlen(va_arg(args, char *));
        if(len > maxLength)
            maxLength = len;
    }

    maxLength += 5;
    repeatChar('_', " ", "\n ", maxLength + 2);
    printf ("\n | %-*s |", maxLength, title);
    repeatChar('-', "|", "\n ", maxLength + 2);

    //list the options
    va_start(args, numOptions);
    for (i = 1; i <= numOptions; i++)
    {
        digitsInOption = log10 (i) + 1;
        char* option = va_arg(args, char *);

        if (digitsInOption > 1)
            printf("\n | %i) %-*s|", i, maxLength - digitsInOption-1 , option);
        else
            printf("\n | %i) %-*s|", i, maxLength -2 , option);
    }

    //textbox part
    repeatChar('_', "|", "\n ", maxLength + 2);
    printf("\n | >%*c|", maxLength, ' ');
    repeatChar('_', "|", "\n ", maxLength + 2);

    va_end(args);

    //put cursor inside box
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor);
    coord.X = 5;
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
        printf("\n --> ERROR: INVALID OPTION\n Try again..");
        return 0;
    }
}


//DISPLAYS AN ORDERED LIST
/// EX. cp_ilist("Select an option", items, 3);
void cp_ilist(char *heading, int items[], int numItems)
{
    int i, j, numDigits, curNumDigits;

    //GET NUMBER OF DIGITS IN THE NUMBER OF ELEMENTS
    //Eg. If numItems = 200 then numDigits = 3
    numDigits = (numItems == 0) ? 1  : (log10(numItems) + 1);

    printf("\n\n  %s\n", heading);
    printf("  ________________________\n");

    // PRINTING EACH ELEMENT
    for(i = 0; i < numItems; i++)
    {
        // GET NUMBER OF DIGITS IN THE CURRENT ITEM's NUMBER
        // Eg. for the 20th element, curNumDigits will be 2
        // for he 1000th element, curNumDigits will be 4
        curNumDigits = (i+1 == 0) ? 1  : (log10(i+1) + 1);
        printf("   %i", i+1);

        //Add spaces to ensure the positions align
        for(j = 0; j < numDigits-curNumDigits; j++)
            printf(" ");

        printf("| %i\n", items[i]); //print the current element of the list
    }
}

/// EX. cp_flist ("Select an option", items, 3);
void cp_flist(char *heading, float items[], int numItems)
{
    int i, j, numDigits, curNumDigits;

    //GET NUMBER OF DIGITS IN THE NUMBER OF ELEMENTS
    //Eg. If numItems = 200 then numDigits = 3
    numDigits = (numItems == 0) ? 1  : (log10 (numItems) + 1);

    printf("\n\n  %s\n", heading);
    printf("  ________________________\n");

    // PRINTING EACH ELEMENT
    for (i = 0; i < numItems; i++)
    {
        // GET NUMBER OF DIGITS IN THE CURRENT ITEM's NUMBER
        // Eg. for the 20th element, curNumDigits will be 2
        // for he 1000th element, curNumDigits will be 4
        curNumDigits = (i+1 == 0) ? 1  : (log10 (i+1) + 1);
        printf("   %i", i+1); // print the order in the list

        //Add spaces to ensure the positions align
        for(j = 0; j < numDigits-curNumDigits; j++)
            printf(" ");

        printf("| %.2f\n", items[i]); //print the current element of the list
    }
}

/// EX. prettify_olist_d("Select an option", RED, items, 3);
void cp_dlist(char *heading, double items[], int numItems)
{
    int i, j, numDigits, curNumDigits;

    //GET NUMBER OF DIGITS IN THE NUMBER OF ELEMENTS
    //Eg. If numItems = 200 then numDigits = 3
    numDigits = (numItems == 0) ? 1  : (log10 (numItems) + 1);

    printf("\n\n  %s\n", heading);
    printf("  ________________________\n");

    // PRINTING EACH ELEMENT
    for (i = 0; i < numItems; i++)
    {
        // GET NUMBER OF DIGITS IN THE CURRENT ITEM's NUMBER
        // Eg. for the 20th element, curNumDigits will be 2
        // for he 1000th element, curNumDigits will be 4
        curNumDigits = (i+1 == 0) ? 1  : (log10 (i+1) + 1);
        printf("   %i", i+1); // print the order in the list

        //Add spaces to ensure the positions align
        for(j = 0; j < numDigits-curNumDigits; j++)
            printf(" ");

        printf("| %lf\n", items[i]); //print the current element of the list
    }
}

/// EX. prettify_olist_c("Select an option", RED, items, 3);
void cp_clist(char *heading, char items[], int numItems)
{
    int i, j, numDigits, curNumDigits;

    //GET NUMBER OF DIGITS IN THE NUMBER OF ELEMENTS
    //Eg. If numItems = 200 then numDigits = 3
    numDigits = (numItems == 0) ? 1  : (log10 (numItems) + 1);

    printf("\n\n  %s\n", heading);
    printf("  ________________________\n");

    // PRINTING EACH ELEMENT
    for (i = 0; i < numItems; i++)
    {
        // GET NUMBER OF DIGITS IN THE CURRENT ITEM's NUMBER
        // Eg. for the 20th element, curNumDigits will be 2
        // for he 1000th element, curNumDigits will be 4
        curNumDigits = (i+1 == 0) ? 1  : (log10 (i+1) + 1);
        printf("   %i", i+1); // print the order in the list

        //Add spaces to ensure the positions align
        for(j = 0; j < numDigits-curNumDigits; j++)
            printf(" ");

        printf("| %c\n", items[i]); //print the current element of the list
    }
}

/// EX. prettify_olist_s("Select an option", RED, items, 3);
void cp_slist(char *heading, char items[][MAX_ARRAY_LENGTH], int numItems)
{
    int i, j, numDigits, curNumDigits;

    //GET NUMBER OF DIGITS IN THE NUMBER OF ELEMENTS
    //Eg. If numItems = 200 then numDigits = 3
    numDigits = (numItems == 0) ? 1  : (log10 (numItems) + 1);

    printf("\n\n  %s\n", heading);
    printf("  ________________________\n");

    // PRINTING EACH ELEMENT
    for (i = 0; i < numItems; i++)
    {
        // GET NUMBER OF DIGITS IN THE CURRENT ITEM's NUMBER
        // Eg. for the 20th element, curNumDigits will be 2
        // for he 1000th element, curNumDigits will be 4
        curNumDigits = (i+1 == 0) ? 1  : (log10 (i+1) + 1);
        printf("   %i", i+1); // print the order in the list

        //Add spaces to ensure the positions align
        for(j = 0; j < numDigits-curNumDigits; j++)
            printf(" ");

        printf("| %s\n", items[i]); //print the current element of the list
    }
}

/// PRINTS A TABLE
void cp_table(char *heading, ...)
{
    int i = 6;
    if (i == 6)
        error("prettify_table", "I is 6");
}

/// PRINT TEXT AT CENTER OF SCREEN
void cp_print(char *format, ...)
{
    va_list args;
    COORD centerPos;
    CONSOLE_SCREEN_BUFFER_INFO csbi; //contains information about the screen
    int screenWwidth;

    va_start(args, format);

    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    screenWwidth = csbi.srWindow.Right - csbi.srWindow.Left + 1;

    /// cursor to center
    centerPos.X = (screenWwidth - strlen(format)) / 2;
    centerPos.Y = csbi.dwCursorPosition.Y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), centerPos);
    /// print
    vprintf(format, args);

    va_end (args);
}

void repeatChar (char ch, char* ends, char* prefix, int times)
{
    printf("%s%s", prefix, ends);

    for (int i = 0; i < times; i++)
        printf ("%c", ch);

    printf("%s", ends);
}
