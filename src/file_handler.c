#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "headers/mainlib.h"

void append2(char* str, char byte) {
    size_t len = strlen(str) + 1;
    str = realloc(str, len);
    if (str == NULL) {
        fputs("FILE_HANDLER ERROR: memory allocation", stderr);
        exit(EXIT_FAILURE);
    }
    str[len - 1] = byte;
    str[len] = '\0';
}

char* file_handler(char* fn) {
    FILE* fp = fopen(fn, "r");
    if (fp == NULL) {
        char* full = malloc(strlen(fn) + strlen(".bb") + 1);
        if (full == NULL) {
            fputs("FILE_HANDLER ERROR: memory allocation", stderr);
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

    char* out = malloc(1);
    if (out == NULL) {
        fputs("FILE ERROR: memory allocation", stderr);
        exit(EXIT_FAILURE);
    }
    out[0] = '\0';
    
    char c;
    while ((c = getc(fp)) != EOF) {
        append2(out, c);
    } 

    fclose(fp);
    return out;
}