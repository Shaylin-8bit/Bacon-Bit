typedef unsigned long long int bytes_8;

typedef struct {
    unsigned char* bytes;
    bytes_8 sze;
} ByteStream;

typedef struct {
    unsigned char field[256];
    unsigned char location;
    bytes_8 loops;
    ByteStream program;
    bytes_8 line;
} Instance;

ByteStream file_handler(char* fn);
ByteStream linter(ByteStream fp);
char** tokenizer(ByteStream buffer);
ByteStream compiler(char** lint);
void interpreter(ByteStream program, char debug);

ByteStream stream(char* module);
void push(ByteStream* str, char byte);
