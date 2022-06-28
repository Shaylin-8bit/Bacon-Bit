typedef struct {
    unsigned char* bytes;
    size_t sze;
} ByteStream;

typedef struct {
    unsigned char field[256];
    unsigned char location;
    size_t loops;
    ByteStream program;
    size_t line;
} Instance;

ByteStream file_handler(char* fn);
ByteStream linter(ByteStream fp);
char** tokenizer(ByteStream buffer);
ByteStream compiler(char** lint);
void interpreter(ByteStream program);

ByteStream stream(char* module);
void push(ByteStream* str, char byte);
