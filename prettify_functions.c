/*
  Programmer    : Shawn Grant
  Date Created  : 13, 09, 2020
  Purpose	    : To mimic GUI elements with text in a console environment
*/

#include "ConsolePrettify.h"

int CUR_COLOR = WHITE;

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
