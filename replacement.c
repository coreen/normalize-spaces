#include <stdio.h>
#include <ctype.h> // isspace

#include "replacement.h"

// https://medium.com/@jraleman/c-programming-language-passing-a-function-as-a-parameter-90d52fe842ea
void process(int tabSize, char drop, FILE* input, FILE* output, char replacement)
{
    // counter variable counts the number of spaces read from user input
    int counter = 0;
    // value variable reads each character input
    int value = 0;
    // w, x , y, and z variables are used in the for loops
    int w = 0;
    int x = 0;
    int y = 0;
    int z = 0;
    // flag variable keeps track of when to print ending TAB/space marker
    int flag = 0;

    char terminate = EOF;
    if (input == stdin) {
    	terminate = '\n';
    }

    // https://beej.us/guide/bgc/html/multi/getc.html
    value = getc(input);
    while (value != terminate) {
        // counts the character accordingly if it is a space character
        if (isspace(value)) {
            if (value == '\n') {
                fprintf(output, "\n");
            } else if (value == '\t') {
                counter += tabSize;
            } else if (value == ' ') {
                counter++;
            }
            flag = 1;
        // printing information to the user through stdout
        // prints the remaining spaces and non-space character read
        } else {
            for (w = 0; w < (counter / tabSize); w++) {
                fprintf(output, "%c", replacement);
            }
            if (drop == 'N') {
                for (x = 0; x < (counter % tabSize); x++) {
                    fprintf(output, " ");
                }
            }
            counter = 0;
            // tests if an ending marker needs to be printed
            if (1 == flag) {
                flag = 0;
            }
            fprintf(output, "%c", value);
        }
        value = getc(input);
    }
    // print any remaining TABs and spaces after last non-space character if requested
    if (drop == 'N') {
        for (y = 0; y < (counter / tabSize); y++) {
            fprintf(output, "%c", replacement);
        }
        for (z = 0; z < (counter % tabSize); z++) {
            fprintf(output, " ");
        }
    }
    fprintf(output, "\n");
}
