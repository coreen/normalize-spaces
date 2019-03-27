// only define functions once
#ifndef _FILE_PROCESSING_H_
#define _FILE_PROCESSING_H_

enum FileType {INPUT, OUTPUT};

char* promptFilename(enum FileType);
FILE* openFile(char*, char*);

#endif // _FILE_PROCESSING_H_