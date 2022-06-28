#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "headers/mainlib.h"

ByteStream linter(ByteStream file) {
    ByteStream buffer = stream("LINTER");

    size_t i = 0;
    char white = 0;

    for (size_t i = 0; i < file.sze; i++) {
        char c = file.bytes[i];
        if (isspace(c)) {
            if (!white) {
                white = 1;
                push(&buffer, '\n');
            }
        } else if (c == ';') {
            while (c != '\n' && c != EOF) {
                c = file.bytes[++i];
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