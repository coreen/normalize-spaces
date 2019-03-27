/*
replace spaces in user input with TAB characters
*/

#include <stdio.h>
#include <ctype.h> // isspace
#include <stdlib.h> // malloc
#include <string.h> // strlen

#include "fileProcessing.h"
#include "replacement.h"

#define TMP_FILENAME "tmp.txt"

void processFile(int tabSize, char drop, char* inputFilename, char* outputFilename)
{

    FILE* inputFile = openFile(inputFilename, "r");
    if (strlen(outputFilename) == 0) {
        outputFilename = TMP_FILENAME;
    }
    FILE* outputFile = openFile(outputFilename, "w");

    process(tabSize, drop, inputFile, outputFile, ' ');

    // close opened files
    fclose(inputFile);
    fclose(outputFile);

    // TODO: if inline replacement requested, replace
}

void processStdin(int tabSize, char drop)
{
    // asks the user for any number of spaces until the user enters a newline
    printf("please enter anything with many TAB characters and spaces (ENTER to process): \n");

    process(tabSize, drop, stdin, stdout, ' ');
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
        // throwaway newline from format entry
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
