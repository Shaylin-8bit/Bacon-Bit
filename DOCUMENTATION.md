<h1> Bacon Bit Documentation </h1>

<h2> Syntax </h2>

Bacon Bit code is broken down into single commands separated by whitespace, many of which require a following byte value.

```
[COMMAND] [BYTE] [COMMAND] [BYTE]
```

Any amount of white space can be used meaning formatting is very lenient.
```
push 5

whil cur
  disn cur
  decr
endl

```
is as valid as
```
push 5 whil cur disn cur decr endl
```
is as valid as
```
    push      5
whil   cur disn

        cur decr 
   endl
```

<h2> Code </h2>

<h3> Commands </h3>

`Non-Byte Commands` are single keywords instructing the system to do something.
<br>They are written on their own with no following byte.
```
brek: force end of current loop
endl: return to start of loop
```


`Byte Commands` are exactly like `Non-Byte Commands` but require the value after them to be a `Byte Value`.
```
back: move number of spaces backwords as next byte indicates
decr: decrement current location by next byte
disc: write next byte to console as character
disn: write next byte to console as number
divi: divide current location by next byte
forw: move number of spaces forward as next byte indicates
incr: increment current location by next byte
modu: divide current location by next byte and save remainder (if next byte 0, 1 used instead)
move: move to the index of the next byte specified
mult: multiply current location by next byte (if next byte 0, 1 used instead)
push: write next byte to current location
whil: while next byte is true run all comands after next byte through next endl
```

<h3> Byte Values </h3>

`Literals` are numerical byte values containing the numbers 0 - 9, or characters wrapped in `'`. 
<br>Because of the languages nature they are limited to the range 0 - 255.
<br>In the event they exceed their limit, the compiler will attempt to wrap them using modulus.
<br>A value exceeding the 64 bit unsigned integer limit may result in undefined behaviour.

<br>The character set includes all single characters along with 3 escape senquences.
```
/n: newline
/t: tab
/b: backspace
```

`Globals` are variable literals provided by the system. 
<br>They function in the same way as `Literals` but represent some value of the systems current state.
```
cur: value stored at current byte
ind: current index
inp: next byte in stdin file
```

<h3> Other </h3>

`Comments` are designated by semicolons `;` and extend to the end of the line.
```
[COMMAND] [BYTE] ; this is a comment about a command requiring a byte
[COMMAND]        ; this is a comment about a command not requiring a byte

[COMMAND]; comments don't need white space
```

<h2> Run Time </h2>

<h3> Linter </h3>
<hr>

A word is interpreted as a group of consecutive characters not including whitespace or semicolons.
The linter loads the input file into memory. It creates a `char*` under `struct Linted` containing all words separated by a newline. This has the exception of comments though. When the linter encounters a semi colon, it skips to the next newline and begins the next word.

| Error               | Issue                         |
|---------------------|-------------------------------|
| `invalid file name` | Input file does not exist     |
| `memory allocation` | Not enough memory at run time |

<h3> Tokenizer </h3>
<hr>

The tokenizer takes a linted object and separates each word into a `char**` that can be read by the compiler.

| Error               | Issue                         |
|---------------------|-------------------------------|
| `memory allocation` | Not enough memory at run time |

<h3> Compiler </h3>
<hr>

The compiler recieves the `char**` ouput from the tokenizer and begins converting them to bytes that the interpreter can run. At each iteration every token is assumed to be a command and mapped from the `COMMANDS` array in "map.h". Bytes 65 - 129 are reserved for commands needing a following byte, so any command mapped to this region causes the compiler to treat the next token as a byte. Bytes in the range 130 - 162 are reserved for commands that don't need a following byte and the compiler simply moves on.

If the command requires a byte the compiler treats the next token as `Byte Value` instead of a `Byte Command` or `Non-Byte Command`. If the next token starts with digit (0 - 9) it is treated as a `Literal Byte Value` and the compiler attempts to convert it to a value between 0 - 255. If it does not start with a digit, it is treated as a `Global Byte Value` and mapped with the `GLOBAL` array in "map.h".

`Byte Values` are wrapped in `Compiler Flags` (byte values 163 - 195) so that the interpreter won't mistake them for other commands. For `Global Byte Values` they are wrapped in the `__global` flag, mapped from the `FLAGS` array in "map.h", and literals with the `__literal` flag, mapped from the `FLAGS` array in "map.h"

| Error                                 | Issue                                                       |
|---------------------------------------|-------------------------------------------------------------|
| `literal value not a number`          | A `Literal Byte Value` contained a non digit character      |
| `memory allocation`                   | Not enough memory at run time                               |
| `EOF missing byte value`              | EOF was encountered right after a `Byte Command`            |
| `EOF loop(s) left open`               | EOF was encountered inside one or more `whil` loops         |
| `endl outside whil (TOKEN_PLACE)`     | An `endl` was found without a matching`whil` at (token num) |
| `invalid token "TOKEN" (TOKEN_PLACE)` | A `Command` was expected but the token could not be mapped  |


<h3> Interpreter </h3>

The interpreter takes the byte stream generated by the compiler and runs an system instance based on each byte given to it. A byte is assumed to be a command. A byte in the range 65 - 129 is a `Byte Command` and one in the range `130 - 162` is a `Non-Byte Command`. If a `Non-Byte Command` is encountered, the interpreter performs the instruction and moves to the next byte. For a `Byte Command` the first byte after is read as a compiler flag indicating if the value is a `Global` or `Literal`, and the second byte after is read as such and the command executed with it. The third byte after is then assumed to be another compiler flag and ignored, and the interpretor moves to the fourth byte after and reads it as the next command.

Special cases exist for the `whil` and `endl` commands. If the byte provided to a `whil` is true execution continues as normal, if it is false the interpretor moves to the coresponding `endl` and execution continues after it. When an `endl` is encountered the interpreter traces backwords to find the coresponding `whil` and execution continue from there. In both cases the interpreter must take care to avoid `Byte Values` as these could correspond to a `whil` or `endl` which is why `Byte Values` are wrapped in special flags.