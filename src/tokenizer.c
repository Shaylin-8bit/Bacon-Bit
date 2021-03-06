#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "include/mainlib.h"

char** tokenizer(ByteStream buffer) {
    unsigned long long int words = 0;
    char** result = NULL;
    char* token = strtok(buffer.bytes, "\n");

    while (token) {
        result = realloc(result, sizeof(char*) * ++words);
        if (result == NULL) {
            fputs("TOKENIZER ERROR: memory allocation failure", stderr);
            exit(EXIT_FAILURE);
        }

        if ((result[words-1] = malloc(strlen(token)+1)) == NULL) {
            fputs("TOKENIZER ERROR: memory allocation failure", stderr);
            exit(EXIT_FAILURE);
        }
        
        strcpy(result[words-1], token);
        token = strtok(NULL, "\n");
    }

    result = realloc(result, sizeof(char*) * (words + 1));
    if (result == NULL) {
        fputs("TOKENIZER ERROR: memory allocation failure", stderr);
        exit(EXIT_FAILURE);
    }

    result[words] = NULL;

    free(buffer.bytes);

    return result;
}