/*
  Programmer    : Shawn Grant
  Date		      : 28,1, 2019
  Purpose	      : Contains structs used in the program and function prototypes
  Filename	    : CYPHER.H
*/

#ifndef CYPHER_H_INCLUDED
#define CYPHER_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "CYPHER.H"
#define MAX 20 //size of the array used to store the list

#define RED 12
#define GREEN 10
#define YELLOW 14
#define BLUE 9
#define WHITE 15
#define CYAN 3
#define GRAY 7

///data type to hold the before and after text of an encryption
typedef struct
{
    char original[500];
    char encoded[700];
    char dateTime[25];
}TextCypher;

typedef struct
{
    TextCypher storage[MAX]; //tool used to store the stack
    int top;
} Stack;

///data type to hold the user
typedef struct
{
    char username[25];
    char password[25];
}User;

/// encoding/decoding
TextCypher Encode(TextCypher);
void Decode(TextCypher);
void SaveToFile(TextCypher);
/// string
void strAppend(char [], char);
void strInsert(char [] ,char [], int);
int strIndexOf(char, char[]);
int strEndsWith(char[], char[]);
int isSymbol(char);
/// history
void AddToHistory(TextCypher);
void ShowHistory();
void Clear();
/// GRAPHICS
void CreateTextBox(char [], void *, int);
void CreateLargeTextBox(char [], void *);
void SplashScreen();
void PrintAtCenterA(char[]);
void PrintAtCenterB(char[], int);
void GoodBye();

// Stack
Stack createStack();
void push(TextCypher, Stack *);
TextCypher pop(Stack *);
bool isFull(Stack);
bool isEmpty(Stack );

#endif // CYPHER_H_INCLUDED
