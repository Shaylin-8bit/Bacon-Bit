#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "headers/mainlib.h"

ByteStream file_handler(char* fn) {
    FILE* fp = fopen(fn, "r");
    if (fp == NULL) {
        char* full = malloc(strlen(fn) + strlen(".bb") + 1);
        if (full == NULL) {
            fputs("FILE_HANDLER ERROR: memory allocation failure", stderr);
            exit(EXIT_FAILURE);
        }
        strcpy(full, fn);
        strcat(full, ".bb");

        fp = fopen(full, "r");
        if (fp == NULL) {
            fputs("FILE_HANDLER ERROR: invalid file name", stderr);
            exit(EXIT_FAILURE);
        }
    }

    ByteStream buffer = stream("FILE_HANDLER");
    
    char c;
    while ((c = getc(fp)) != EOF) {
        push(&buffer, c);
    } 

    fclose(fp);
    return buffer;
}