#include <stdio.h>
#include <stdlib.h> // malloc
#include <string.h> // strlen

#include "fileProcessing.h"

/*
	Prompts the user for the specified type of file and returns the validated user inputted filename

	Args:
	- type: FileType from enum defined in the header file, changes user prompt for filename

	Return:
	- User inputted filename or empty string if greater than buffer size
*/
char* promptFilename(enum FileType fileType)
{
	// asks the user for a file to process
    // filepath can be relative
    size_t bufferSize = 50;
    size_t characterCount;

    char* filename;
    filename = (char*) malloc(bufferSize * sizeof(char));
    if (filename == NULL) {
        printf("error allocating space for filename, exiting\n");
        return "";
    }
	
	// intialize with longer of 2 possible types
	char* type = "output";
	if (fileType == INPUT) {
		type = "input";
	}

    printf("please enter the %s file to process: \n\t", type);
    characterCount = getline(&filename, &bufferSize, stdin);
    if (characterCount > bufferSize) {
        printf("filename length is longer than %zu character limit, exiting\n", bufferSize);
        return "";
    }

    // remove extra newline char from end of stdin input
    // https://stackoverflow.com/questions/36635063/using-fopen-with-input-filenames-in-c
    size_t len = strlen(filename);
    if (len > 0 && filename[len - 1] == '\n') {
        filename[len - 1] = '\0';
    }

    return filename;
}

/*
	Attempts to open the specified filename and returns file pointer if successful

	Args:
	- filename: name of file to attempt to open
	- mode: file access permissions requested

	Return:
	- File pointer to specified filename or NULL if failed to open
*/
FILE* openFile(char* filename, char* mode)
{
    // opens file for processing
    FILE* file;
    file = fopen(filename, mode); //EXAMPLE: "r" or "w"
    if (file == NULL) {
        printf("error opening file, exiting\n");
        return NULL;
    }
    return file;
}
