#include <stdio.h>
#include <stdlib.h>
#include "headers/mainlib.h"

int main(int argc, char* argv[]) {

    if (argc < 2) {
        puts("ERROR: no input file");
        exit(EXIT_FAILURE);
    }

    char* file = file_handler(argv[1]);
    Linted linted = linter(file);
    char** tokens = tokenizer(linted);
    Compiled compiled = compiler(tokens);
    interpreter(compiled);

    return 0;
}