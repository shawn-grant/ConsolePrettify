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
  Programmer  : Shawn Grant
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
#include <stdarg.h>
#include <math.h>

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

//input
void prettify_textcolor(int);
void prettify_textbox(char [], void *, int);
void prettify_textbox_password(char *, char, int);
void prettify_textbox_large(char [], void *, int);

void prettify_textbox_centered(char [], void *, int);
void prettify_textbox_password_centered(char [], void *, int);
void prettify_textbox_large_centered(char [], void *, int);

//text
void prettify_print(char[], int);

//table
void prettify_table(char **, int, int, ...);

//menu
int prettify_menu(char *, int, int, ...);

//ordered lists
void prettify_olist_i(char *, int, int[]);
void prettify_olist_f(char *, int, float[]);
void prettify_olist_d(char *, int, double[]);
void prettify_olist_c(char *, int, char[]);
void prettify_olist_s(char *, int, char**);

#endif // CONSOLEPRETTIFY_H_INCLUDED
