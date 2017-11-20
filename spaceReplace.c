/*
replace spaces in user input with TAB characters
*/

#include<stdio.h>
#include <ctype.h>

int main(void)
{
    // tabSize variable is the user inputted space-to-tab equivalent
    int tabSize = 4; // default is 4
    // value variable reads each character input
    int value = 0;
    // counter variable counts the number of spaces read from user input
    int counter = 0;
    // w, x , y, and z variables are used in the for loops
    int w = 0;
    int x = 0;
    int y = 0;
    int z = 0;
    // drop variable keeps track of whether or not to print trailing spaces
    char drop = '\0';
    // flag variable keeps track of when to print ending TAB/space marker
    int flag = 0;

    // reading information from the user through stdin
    // asks the user for tab-to-space equivalent
    printf("please enter the number of spaces a TAB character should equal: \n");
    tabSize = getchar() - '0'; // convert char into int
    // throwaway newline for tabSize entry
    getchar();

    // asks the user whether or not to drop trailing spaces after tab conversion
    printf("do you want trailing spaces after TAB conversion to be dropped? [Y/N]: \n");
    drop = getchar();
    if (drop  == 'Y') {
        printf("dropping trailing spaces\n");
    } else {
        if (drop != 'N') {
            printf("invalid response entered, leaving spaces in conversion\n");
        }
        printf("leaving spaces in conversion requested\n");
    }
    // throwaway newline for drop entry
    getchar();

    // asks the user for any number of spaces until the user enters a newline
    printf("please enter anything with many TAB characters and spaces (ENTER to process): \n");
    value = getchar();
    while (value != '\n') {
        // counts the character accordingly if it is a space character
        if (isspace(value)) {
            if (value == '\t') {
                counter+=tabSize;
            } else if (value == ' ') {
                counter++;
            }
            flag = 1;
        // printing information to the user through stdout
        // prints the remaining spaces and non-space character read
        } else {
            for (w = 0; w < (counter / tabSize); w++) {
                printf("\t");
            }
            if (drop == 'Y') {
                for (x = 0; x < (counter % tabSize); x++) {
                    printf(" ");
                }
            }
            counter = 0;
            // tests if an ending marker needs to be printed
            if (1 == flag) {
                flag = 0;
            }
            putchar(value);
        }
        value = getchar();
    }
    // print any remaining TABs and spaces after last non-space character
    for (y = 0; y < (counter / tabSize); y++) {
        printf("\t");
    }
    // trailing spaces
    if (drop == 'Y') {
        for (z = 0; z < (counter % tabSize); z++) {
            printf(" ");
        }
    }
    printf("\n");

    return 0;
}
