#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "include/mainlib.h"
#include "include/flags.h"

ByteStream linter(ByteStream file) {
    ByteStream buffer = stream("LINTER");

    bytes_8 i = 0;
    char white = 0;

    for (bytes_8 i = 0; i < file.sze; i++) {
        char c = file.bytes[i];
        if (isspace(c)) {
            if (!white) {
                white = 1;
                push(&buffer, WORD_SEPARATOR);
            }
        } else if (c == SINGLE_LINE_COMMENT) {
            while (c != ENDLINE && c != EOF) {
                c = file.bytes[++i];
            }
            if (!white) {
                white = 1;
                push(&buffer, WORD_SEPARATOR);
            }
        } else if (c == MULTI_LINE_COMMENT) {
            do {
                c = file.bytes[++i];
            } while (c != MULTI_LINE_COMMENT && c != EOF);
            if (!white) {
                white = 1;
                push(&buffer, WORD_SEPARATOR);
            }
        } else if (c == STRING) {
            do {
                push(&buffer, c);
                c = file.bytes[++i];
            } while (c != STRING && c != EOF);
            white = 1;
            push(&buffer, STRING);
            push(&buffer, WORD_SEPARATOR);
        } else {
            white = 0;
            push(&buffer, c);
        }
    }

    return buffer;
}