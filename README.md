<h1> Bacon Bit </h1>

Bacon Bit was inspired by playing with a Turing Machine, when I wondered how much could be done with a very small limit on bytes. The environment only allows the programmer a memory field of 255 bytes to work with, and only allows one of those bytes to be read from and written to at once. There are a couple other "global" values the environment allows you to use, from any memory location. These are your current location, and the next byte in the stdin file. Other than that the user is allowed to use literals, or hardcoded byte values.

The field you are given is initialized with all bytes set to 0, and your location at 0. From there you can read from and write to your current byte, move forwards or backwords any number of spaces, jump to a specific location, get input from stdin, and write values to stdout.

<h2> Setup </h2>

<h3> Compiling </h3>
Prerequisites:

* A standard C compiler (gcc and tcc have both been shown to work)
* Support for Makefiles

1. Clone this repository
2. In Makefile set the `COM` flag to your compiler, and `OUT` to desired executable name
3. Run `make` command
4. A binary with the name specified by `OUT` will be created

<h3> Usage </h3>
For ease of use, recommend adding "baconbit" to environment path, but this is not strictly needed. 

Baconbit files are saved with the prefix.bb, though you can instruct the interpreter to attempt running any file.
To run a file, simple run your executable with the file path desired. If the file is not found, the linter will search for it again with `.bb` appended to it.

In windows this would look like:
```
baconbit.exe file.bb
```
or
```
baconbit.exe file
```

<h2> Documentation </h2>

To learn how to use the language, check <a href="./DOCUMENTATION.md"> DOCUMENTATION.md </a>

<h2> Contributing </h2>

Interested in contributing? Check <a href="./CONTRIBUTING.md"> CONTRIBUTING.md </a>
 