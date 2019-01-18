/*
replace spaces in user input with TAB characters
*/

#include <stdio.h>
#include <ctype.h>
#include <stdlib.h> // malloc
#include <string.h> // strlen

void processFile(void)
{
    // asks the user for a file to process
    // filepath can be relative
    size_t bufferSize = 50;
    size_t characterCount;

    char* filename;
    filename = (char*) malloc(bufferSize * sizeof(char));
    if (filename == NULL) {
        printf("error allocating space for filename, exiting\n");
        return;
    }

    printf("please enter the file to process: \n");
    characterCount = getline(&filename, &bufferSize, stdin);
    if (characterCount > bufferSize) {
        printf("filename length is longer than %zu character limit, exiting\n", bufferSize);
        return;
    }

    // remove extra newline char from end of stdin input
    // https://stackoverflow.com/questions/36635063/using-fopen-with-input-filenames-in-c
    size_t len = strlen(filename);
    if (len > 0 && filename[len - 1] == '\n') {
        filename[len - 1] = '\0';
    }

    // opens file for processing
    FILE* file;
    file = fopen(filename, "r");
    if (file == NULL) {
        printf("error opening file, exiting\n");
        return;
    }

    printf("here\n");
}

void processStdin(int tabSize, char drop)
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
    printf("please enter the number of spaces a TAB character should equal: \n");
    tabSize = getchar() - '0'; // convert char into int
    // throwaway newline for tabSize entry
    getchar();

    // asks the user whether or not to drop trailing spaces after tab conversion
    printf("do you want trailing spaces after TAB conversion to be dropped? [Y/N]: \n");
    drop = getchar();
    if (drop == 'Y') {
        printf("dropping trailing spaces\n");
    } else if (drop != 'N') {
        printf("leaving spaces in conversion requested\n");
    } else {
        printf("invalid response entered, leaving spaces in conversion\n");
    }
    // throwaway newline for drop entry
    getchar();

    // asks the user for input type
    printf("what type of input will be provided? [F(ile)/S(tdin)]: \n");
    input = getchar();

    // throwaway newline from input entry
    getchar();

    if (input == 'F') {
        processFile();
    } else if (input == 'S') {
        processStdin(tabSize, drop);
    } else {
        printf("invalid input type received, exiting\n");
    }

    return 0;
}
