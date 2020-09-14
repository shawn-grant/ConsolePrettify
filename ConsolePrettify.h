/*
  Programmer    : Shawn Grant
  Date		    : 28,1, 2019
  Purpose	    : Contains any structs used in the program and function prototypes
*/

#ifndef CONSOLEPRETTIFY_H_INCLUDED
#define CONSOLEPRETTIFY_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <ctype.h>
#include <windows.h>

/// COLORS
#define RED 12
#define GREEN 10
#define LIGHT_BLUE 11
#define YELLOW 6
#define LIGHT_YELLOW 14
#define BLUE 9
#define PURPLE 5
#define WHITE 15
#define CYAN 3
#define GRAY 7
#define DARK_GRAY 8

void prettify_textcolor(int);
void prettify_textbox(char [], void *, int);
void prettify_textbox_password(char *, char, int);
void prettify_textbox_large(char [], void *, int);

void prettify_textbox_centered(char [], void *, int);
void prettify_textbox_password_centered(char [], void *, int);
void prettify_textbox_large_centered(char [], void *, int);

void prettify_print_centered_A(char[]);
void prettify_print_centered_B(char[], int);

#endif // CONSOLEPRETTIFY_H_INCLUDED
