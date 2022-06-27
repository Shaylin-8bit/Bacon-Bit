typedef struct {
    unsigned char* bytes;
    size_t sze;
} Compiled;

typedef struct {
    unsigned char* str;
    size_t sze;
} Linted;

typedef struct {
    unsigned char field[256];
    unsigned char location;
    size_t loops;
    Compiled program;
    size_t line;
} Instance;

Linted linter(char* fp);
char** tokenizer(Linted buffer);
Compiled compiler(char** lint);
void interpreter(Compiled program);
