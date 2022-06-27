#include <stdio.h>
#include <stdlib.h>
#include "headers/mainlib.h"

int main(int argc, char* argv[]) {

    if (argc < 2) {
        puts("ERROR: no input file");
        exit(EXIT_FAILURE);
    }

    Linted linted = linter(argv[1]);
    char** tokens = tokenizer(linted);
    Compiled compiled = compiler(tokens);

    interpreter(compiled);

    return 0;
}