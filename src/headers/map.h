#include <stdio.h>

typedef struct {
  char* word;
  char byte;
} Token;

const Token GLOBALS[4] = {
// Globals 1 - 64
  (Token) {"ind", 1},
  (Token) {"cur", 2},
  (Token) {"inp", 3},
  (Token) {NULL, 0},
};

const Token COMMANDS[12] = {
// Commands (using next byte) 65 - 129
  (Token) {"move", 65},
  (Token) {"forw", 66},
  (Token) {"back", 67},
  (Token) {"push", 68},
  (Token) {"disc", 69},
  (Token) {"disn", 70},
  (Token) {"whil", 71},
  (Token) {"incr", 72},
  (Token) {"decr", 73},
  
// Commands (not using next byte) 130 - 162
  (Token) {"endl", 130},
  (Token) {"brek", 131},
  (Token) {NULL, 0},
};

const Token FLAGS[3] = {
// Compiler Flags 163 - 195
  (Token) {"__literal", 163},
  (Token) {"__global", 164},
  (Token) {NULL, 0},
};