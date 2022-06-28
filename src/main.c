#include <stdio.h>
#include <stdlib.h>
#include "include/mainlib.h"

int main(int argc, char* argv[]) {

    if (argc < 2) {
        puts("ERROR: no input file");
        exit(EXIT_FAILURE);
    }

    ByteStream file = file_handler(argv[1]);
    ByteStream linted = linter(file);
    char** tokens = tokenizer(linted);
    ByteStream compiled = compiler(tokens);
    interpreter(compiled, 0);

    return 0;
}