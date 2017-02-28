/*
replaces TAB characters in user input with spaces, assumes TAB = 4 spaces
*/

#include<stdio.h>
#include <ctype.h>

int main(void)
{
    // value variable reads each character input
    int value = 0;
    // counter variable counts the number of spaces read from user input
    int counter = 0;
    // tabs variable keeps track of the number of tabs to print
    int tabs = 0;
    // x , y, and z variables are used in the for loops
    int x = 0;
    int y = 0;
    int z = 0;
    // flag variable keeps track of when to print ending TAB/space marker
    int flag = 0;

    // reading information from the user through stdin
    // asks the user for any number of spaces until the user enters a newline
    printf("please enter anything with many spaces (ENTER to process): \n");
    value = getchar();
    while (value != '\n') {
        // counts the character accordingly if it is a space character
        if (isspace(value)) {
            counter++;
            flag = 1;
            if (4 == counter) {
                printf("|    ");
                counter = 0;
            }
        // printing information to the user through stdout
        // prints the remaining spaces and non-space character read
        } else {
            for (x = 0; x < counter; x++) {
                printf("| ");
            }
            counter = 0;
            // tests if an ending marker needs to be printed
            if (1 == flag) {
                printf("|");
                flag = 0;
            }
            putchar(value);
        }
        value = getchar();
    }
    // print any remaining TABs and spaces after last non-space character
    for (y = 0; y < (counter / 4); y++) {
        printf("|    ");
    }
    for (z = 0; z < (counter % 4); z++) {
        printf("| ");
    }
    printf("|\n");

    return 0;
}
