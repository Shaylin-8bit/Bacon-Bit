#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "headers/mainlib.h"

void push(Linted* str, char byte) {
    str->sze++;
    str->str = realloc(str->str, str->sze+1);
    if (str->str == NULL) {
        fputs("LINTER ERROR: memory allocation", stderr);
        exit(EXIT_FAILURE);
    }
    
    str->str[str->sze - 1] = byte;
    str->str[str->sze] = '\0';
}


Linted linter(char* fn) {
    FILE* fp = fopen(fn, "r");
    if (fp == NULL) {
        char* full = malloc(strlen(fn) + strlen(".bb") + 1);
        if (full == NULL) {
            fputs("LINTER ERROR: memory allocation", stderr);
            exit(EXIT_FAILURE);
        }
        strcpy(full, fn);
        strcat(full, ".bb");

        fp = fopen(full, "r");
        if (fp == NULL) {
            fputs("LINTER ERROR: invalid file name", stderr);
            exit(EXIT_FAILURE);
        }
    }
    
    Linted buffer = {
        malloc(1), 
        0
    };

    if (buffer.str == NULL) {
        fputs("LINTER ERROR: memory allocation", stderr);
        exit(EXIT_FAILURE);
    }

    buffer.str[0] = '\0';

    size_t i = 0;
    char c;
    char white = 0;

    for (size_t j = 0; (c = getc(fp)) != EOF; j++) {
        if (isspace(c)) {
            if (!white) {
                white = 1;
                push(&buffer, '\n');
            }
        } else if (c == ';') {
            while (c != '\n' && c != EOF) {
                c = getc(fp);
            }
            if (!white) {
                white = 1;
                push(&buffer, '\n');
            }
        } else {
            white = 0;
            push(&buffer, c);
        }
    }

    push(&buffer, '\0');
    fclose(fp);
    return buffer;
}