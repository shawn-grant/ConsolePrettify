# Console Prettify🎨 (alpha)
A simple tool for making good UI in C/C++ console apps with little effort.

## How to Use 🖥️
Download or clone this repository. Copy `prettify_functions.c` and `ConsolePrettify.h` into your project folder and add `#include "ConsolePrettify.h"` in your C/C++ files.

Make sure the new files are correctly linked in your IDE/compiler.

## Available Functions

Function | Description
--- | --- 
`void prettify_textcolor(color)` | Changes the text color
`void prettify_textbox(specifier, variable, color)` | Displays an input field and reads user input
`void prettify_textbox_password(variable, mask, color)` | Displays an input field with masking eg. *****
`int prettify_menu(title, color, numOptions, ...)` | Displays a menu and returns the number of the selected option
`void prettify_list_ordered(title, color, items)` | Displays an ordered list of items


---
> _**NOTE**: Please use `prettify_textcolor()` for all colored text in your program._.

<br>

## Available Colors 🌈
use any of these constants as the color arguments of prettify functions
Constant Name | Value
--- | --- 
RED | 12
GREEN |  10
LIGHT_BLUE | 11
YELLOW | 6
LIGHT_YELLOW | 14
BLUE | 9
PURPLE | 5
WHITE | 15
CYAN | 3
GRAY | 7
DARK_GRAY | 8

<br>

# Examples
### Textboxes:

```c
int num;
char password[25];

printf("THIS IS A TEXTBOX");
prettify_textbox("%i", &num, YELLOW);

printf("\nTHIS IS A PASSWORD TEXTBOX");
prettify_textbox_password(password, '+', BLUE);
```
> Output:

> ![Output](images/output1.PNG)


### Menus
```c
int choice = prettify_menu("Select an option", RED, 4,
                  "Buy bananas",
                  "Buy apple",
                  "Buy mango",
                  "Buy grapes");
```
> Output:
<br>
![Output](images/output2.PNG)


### Lists
```c
char **people = {"Justin", "Kim", "Susan"};
prettify_list_ordered("List of People", GREEN, people);
```
> Output:
<br>
![Output](images/output3.PNG)

## TODO
- Add automatic Table printing
- Print to center
