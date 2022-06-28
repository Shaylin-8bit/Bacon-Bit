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


Linted linter(char* file) {
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

    for (size_t j = 0; (c = file[j]) != '\0'; j++) {
        if (isspace(c)) {
            if (!white) {
                white = 1;
                push(&buffer, '\n');
            }
        } else if (c == ';') {
            while (c != '\n' && c != EOF) {
                c = file[++j];
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
    return buffer;
}