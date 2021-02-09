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
///DO NOT CHANGE THESE
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

/// GLOBAL VARS
#define MAX_ARRAY_LENGTH 50
#define OLIST_SEPARATOR " )" //displayed between the item number and the item eg. 32 ) Bread
#define ULIST_BULLET "*" // bullet point displayed before each item in the list eg. * item 1, * item 2

typedef struct {
    char heading[25];
    void * items;
    char dataType;
}TableColumn;

//input
void cp_textcolor(int);
void cp_textbox(char *, void *);
void cp_password(char *);

//text
void cp_print(char *, ...);

//table
void cp_table(char *, ...);

//menu
int cp_menu(char *, int, ...);
int cp_menu2(char *, int, ...);

//ordered lists
void cp_ilist(char *, int[], int);
void cp_flist(char *, float[], int);
void cp_dlist(char *, double[], int);
void cp_clist(char *, char[], int);
void cp_slist(char *, char[][MAX_ARRAY_LENGTH], int);

void repeatChar (char ch, char* ends, char* prefix, int times);

#endif // CONSOLEPRETTIFY_H_INCLUDED
