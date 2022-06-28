#include <stdio.h>
#include <stdlib.h>
#include "include/mainlib.h"

void push(ByteStream* stream, char byte) {
    stream->sze++;
    stream->bytes = realloc(stream->bytes, stream->sze+1);
    if (stream->bytes == NULL) {
        return;
    }
    
    stream->bytes[stream->sze - 1] = byte;
    stream->bytes[stream->sze] = '\0';
}

ByteStream stream(char* module) {
    ByteStream buffer = {
        malloc(1), 
        0
    };

    if (buffer.bytes == NULL) {
        fprintf(stderr, "%s ERROR: memory allocation failure", module);
        exit(EXIT_FAILURE);
    }

    buffer.bytes[0] = '\0';

    return buffer;
}