#include <stdio.h>
#include <stdlib.h>
#include "headers/mainlib.h"

unsigned char get_val(unsigned char type, unsigned char value, unsigned char* field, unsigned char location) {
    if (type == 163) return value;
    if (type == 164) {
        switch (value) {
            case 1:
            return location;

            case 2:
            return field[location];

            case 3:
            return getchar();
        }
    }
}


Instance new_instance(ByteStream bytes) {
    Instance r;
    r.location = 0;
    r.line = 0;
    r.program = bytes;
    r.loops = 0;
    for (int i = 0; i <= 255; i++) {
        r.field[i] = 0;
    } 
    return r;
}


void run_next(Instance* instance, char debug) {

    unsigned char c = instance->program.bytes[instance->line];
    if (debug) printf("BYTE:: %d\tLINE:: %llu\tCUR:: %d\tIND:: %d\n", c, instance->line+1, instance->field[instance->location], instance->location);

    if (c >= 65 && c <= 129) {
        unsigned char nb1 = instance->program.bytes[instance->line+1];
        unsigned char nb2 = instance->program.bytes[instance->line+2];
        unsigned char byte = get_val(
            nb1,
            nb2,
            instance->field,
            instance->location
        );

        

        switch (c) {
            case 65:  // move to location
            instance->location = byte;
            instance->line += 4;
            break;

            case 66:  // move forwards from location
            instance->location += byte;
            instance->line += 4;
            break;

            case 67:  // move backwords from location
            instance->location -= byte;
            instance->line += 4;
            break;

            case 68:  // write to current location
            instance->field[instance->location] = byte;
            instance->line += 4;
            break;
            
            case 69:  // print in character format
            putchar(byte);
            instance->line += 4;
            break;

            case 70:  // print in number format
            printf("%d", byte);
            instance->line += 4;
            break;

            case 71:  // start while loop skip ahead if false, endl (130) responsible for return
            if (!byte) {
                instance->line += 4;
                while (1) {
                    c = instance->program.bytes[instance->line];
                    if (c == 71) {
                        instance->loops += 1; 
                        instance->line += 4;
                    } else if (c != 130) {
                        if (c >= 65 && c <= 129) instance->line += 4;
                        else instance->line += 1;
                    } else {
                        if (instance->loops > 0) {
                            instance->loops -= 1;
                            instance->line += 4;
                        } else {
                            instance->line += 1;
                            break;
                        }
                    }
                } 
            } else {
                instance->line += 4;
            }
            break;
            
            case 72: // increment current byte
            instance->field[instance->location] += byte;
            instance->line += 4;
            break;

            case 73: // decrement current byte
            instance->field[instance->location] -= 1;
            instance->line += 4;
            break;
        }
    } else if (c >= 130 && c <= 162) {
        switch (c) {
            case 130:  // end of loop
            instance->line -= 1;
            while (1) {
                c = instance->program.bytes[instance->line]; 
                if (c == 130) {
                    instance->loops += 1;
                    instance->line -= 1;
                } else if (c == 163 || c == 164) {
                    instance->line -= 3;
                } else if (c == 71) {
                    if (instance->loops > 0) {
                        instance->loops -= 1;
                        instance->line -= 1;
                    } else {
                        break;
                    }
                } else {
                    instance->line -= 1;
                }
            } 
            break;

            case 131:  // break loop or program
            instance->line += 1;
            while (1) {
                c = instance->program.bytes[instance->line];
                if (c == 163 || c == 164) {
                    instance->line += 3;
                } else if (c == 130) {
                    instance->line += 1;
                    break;
                } else {
                    instance->line += 1;
                }
            }
            break;
        }
    } else {
        fprintf(stderr, "INTERPRETER ERROR: invalid command %d at %llu\n", c, instance->line);
        exit(EXIT_FAILURE);
    }
}


void interpreter(ByteStream program, char debug) {
    Instance main_instance = new_instance(program);
    while (main_instance.line < main_instance.program.sze) {
        run_next(&main_instance, debug);
    }
}