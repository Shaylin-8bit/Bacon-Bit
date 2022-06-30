#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "include/map.h"
#include "include/mainlib.h"
#include "include/flags.h"

unsigned long long raise(unsigned long long base, unsigned long long exp) {
    if (exp == 0) return 1;
    unsigned long long result = base;
    for (unsigned long long i = 1; i < exp; i++) result *= base;
    return result; 
}

unsigned char toint(char* str) {
    unsigned long long int result = 0;
    unsigned long long int mult = raise(10, strlen(str)-1);
    for (bytes_8 i = 0; i < strlen(str); i++) {
        if (str[i] < '0' || str[i] > '9') {
            fputs("COMPILER ERROR: literal value not a number", stderr);
            exit(EXIT_FAILURE);
        }
        result += mult * (str[i]-'0');
        mult /= 10;
        if (result > 255) {
            result %= 256;
        } 
    }
    return result;
}

unsigned char tochar(char* str) {
    bytes_8 len = strlen(str);
    if ((len < 3 || len > 4) || (len > 3 && str[1] != '\\')) {
        fputs("COMPILER ERROR: literal value not a valid char", stderr);
        exit(EXIT_FAILURE);
    } 
    if (len == 3) return str[1];
    switch(str[2]) {
        case 'n':
        return '\n';

        case 't':
        return '\t';

        case 'b':
        return '\b';

        default:
        fputs("COMPILER ERROR: literal value not a valid character", stderr);
        exit(EXIT_FAILURE);
    }
}

unsigned char get_command_byte(char* str) {
    for (bytes_8 i = 0; COMMANDS[i].word != NULL; i++) {
        if (!strcmp(str, COMMANDS[i].word)) return COMMANDS[i].byte;
    }
    return 0;
}


unsigned char get_global_byte(char* str) {
    for (bytes_8 i = 0; GLOBALS[i].word != NULL; i++) {
        if (!strcmp(str, GLOBALS[i].word)) return GLOBALS[i].byte;
    }
    return 0;
}


unsigned char get_flag_byte(char* str) {
    for (bytes_8 i = 0; FLAGS[i].word != NULL; i++) {
        if (!strcmp(str, FLAGS[i].word)) return FLAGS[i].byte;
    }
    return 0;
}

ByteStream compiler(char** lint) {

    ByteStream result = stream("COMPILER");
    long long loops = 0;
    
    for (bytes_8 i = 0; lint[i]; i++) {
        char* token = lint[i];
        unsigned char byte = get_command_byte(token);

        if (byte >= 65 && byte <= 129) {
            if (byte == get_command_byte("whil")) ++loops;
            push(&result, byte);
            char* next = lint[++i];

            if (next == NULL) {
                fputs("COMPILER ERROR: unexpected EOF missing byte value", stderr);
                exit(EXIT_FAILURE);
            }

            if (next[0] >= '0' && next[0] <= '9') {
                unsigned char nbyte = toint(next);
                push(&result, get_flag_byte("__literal"));
                push(&result, nbyte);
                push(&result, get_flag_byte("__literal"));
            
            } else if (strlen(next) >= 3 && next[0] == STRING && next[strlen(next)-1] == STRING) {
                push(&result, get_flag_byte("__literal"));
                push(&result, tochar(next));
                push(&result, get_flag_byte("__literal"));

            } else {
                unsigned char nbyte = get_global_byte(next);
                if (!nbyte) {
                    fprintf(stderr, "COMPILER ERROR: Invalid Token at %llu: \"%s\" must be byte value", i+1, next);
                    exit(EXIT_FAILURE);
                }
                push(&result, get_flag_byte("__global"));
                push(&result, nbyte);
                push(&result, get_flag_byte("__global"));
            }

        } else if (byte) {
            push(&result, byte);
            if (byte == get_command_byte("endl")) --loops;
            if (loops < 0) {
                fprintf(stderr, "COMPILER ERROR: endl outside whil (%llu)", i+1);
                exit(EXIT_FAILURE);
            }
        } else {
            fprintf(stderr, "COMPILER ERROR: invalid token \"%s\" (%llu)", token, i+1);
            exit(EXIT_FAILURE);
        }
    }

    if (loops > 0) {
        fputs("COMPILER ERROR: EOF loop(s) left open", stderr);
        exit(EXIT_FAILURE);
    }

   return result;
}
