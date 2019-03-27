/*
replace spaces in user input with TAB characters
*/

#include <stdio.h>
#include <ctype.h>
#include <stdlib.h> // malloc
#include <string.h> // strlen

#include "fileProcessing.h"

#define TMP_FILENAME "tmp.txt"

// https://medium.com/@jraleman/c-programming-language-passing-a-function-as-a-parameter-90d52fe842ea
void process(int tabSize, char drop, FILE* input, FILE* output)
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

    // https://beej.us/guide/bgc/html/multi/getc.html
    value = getc(input);
    while (value != EOF) {
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
                fprintf(output, "\t");
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
            fprintf(output, "\t");
        }
        for (z = 0; z < (counter % tabSize); z++) {
            fprintf(output, " ");
        }
    }
    fprintf(output, "\n");
}

void processFile(int tabSize, char drop, char* inputFilename, char* outputFilename)
{

    FILE* inputFile = openFile(inputFilename, "r");
    if (strlen(outputFilename) == 0) {
        outputFilename = TMP_FILENAME;
    }
    FILE* outputFile = openFile(outputFilename, "w");

    process(tabSize, drop, inputFile, outputFile);

    // close opened files
    fclose(inputFile);
    fclose(outputFile);

    // TODO: if inline replacement requested, replace
/*
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

    value = fgetc(inputFile);
    while (value != EOF) {
        // counts the character accordingly if it is a space character
        if (isspace(value)) {
            if (value == '\n') {
                printf("\n");
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
                ////TODO: replace with fprintf, resource => https://stackoverflow.com/questions/11573974/write-to-txt-file
                printf("\t");
            }
            if (drop == 'N') {
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
        value = fgetc(file);
    }
    // print any remaining TABs and spaces after last non-space character if requested
    if (drop == 'N') {
        for (y = 0; y < (counter / tabSize); y++) {
            printf("\t");
        }
        for (z = 0; z < (counter % tabSize); z++) {
            printf(" ");
        }
    }
    printf("\n");
*/
}

void processStdin(int tabSize, char drop)
{
    // asks the user for any number of spaces until the user forces EOF
    // https://stackoverflow.com/questions/28216437/end-of-file-in-stdin
    // NOTE: support recommended is for Windows key binding
    printf("please enter anything with many TAB characters and spaces (Ctrl-Z to process): \n");

    process(tabSize, drop, stdin, stdout);
/*
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

    // asks the user for any number of spaces until the user enters a newline
    printf("please enter anything with many TAB characters and spaces (ENTER to process): \n");
    value = getchar();
    while (value != '\n') {
        // counts the character accordingly if it is a space character
        if (isspace(value)) {
            if (value == '\t') {
                counter += tabSize;
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
            if (drop == 'N') {
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
    // print any remaining TABs and spaces after last non-space character if requested
    if (drop == 'N') {
        for (y = 0; y < (counter / tabSize); y++) {
            printf("\t");
        }
        for (z = 0; z < (counter % tabSize); z++) {
            printf(" ");
        }
    }
    printf("\n");
*/
}

int main(void)
{
    // tabSize variable is the user inputted space-to-tab equivalent
    int tabSize = 4; // default is 4
    // drop variable keeps track of whether or not to print trailing spaces
    char drop = '\0';
    // input variable keeps track of type of processing to perform
    char input = '\0';

    // reading information from the user through stdin
    // asks the user for tab-to-space equivalent
    printf("please enter the number of spaces a TAB character should equal: \n\t");
    tabSize = getchar() - '0'; // convert char into int
    // throwaway newline for tabSize entry
    getchar();

    // asks the user whether or not to drop trailing spaces after tab conversion
    printf("do you want trailing spaces after TAB conversion to be dropped? [Y/N]: \n\t");
    drop = getchar();
    if (drop == 'Y') {
        printf("dropping trailing spaces\n");
    } else if (drop == 'N') {
        printf("leaving spaces in conversion requested\n");
    } else {
        printf("invalid response entered, leaving spaces in conversion\n\t");
    }
    // throwaway newline for drop entry
    getchar();

    // asks the user for input type
    printf("what type of input will be provided? [F(ile)/S(tdin)]: \n\t");
    input = getchar();

    // throwaway newline from input entry
    getchar();

    if (input == 'F') {
        char* inputFilename = promptFilename(INPUT);
        size_t bufferSize = 50;
        char* outputFilename = (char*) malloc(bufferSize * sizeof(char));;

        // ask the user for output type
        printf("how should output be formatted? [I(nline)/E(xternal File)]: \n\t");
        input = getchar();
        // throwaway newline
        getchar();
        if (input == 'E') {
            outputFilename = promptFilename(OUTPUT);
        } else {
            outputFilename = "";
        }

        processFile(tabSize, drop, inputFilename, outputFilename);
    } else if (input == 'S') {
        processStdin(tabSize, drop);
    } else {
        printf("invalid input type received, exiting\n");
    }

    return 0;
}
