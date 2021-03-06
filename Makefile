COM = gcc       # Set to your compilers command
OUT = baconbit  # Set to output name of executable

SRC = src/
HED = $(SRC)include/

UNAME := $(shell uname)
ifeq ($(UNAME), Linux)
COMMAND = rm
else
COMMAND = del
endif

main: main.o file_handler.o linter.o tokenizer.o compiler.o interpreter.o util.o $(HED)mainlib.h $(HED)map.h
	$(COM) -o $(OUT) main.o file_handler.o linter.o tokenizer.o compiler.o interpreter.o util.o
	make clean

main.o: $(SRC)main.c $(HED)mainlib.h
	$(COM) -c $(SRC)main.c

file_handler.o: $(SRC)file_handler.c $(HED)mainlib.h
	$(COM) -c $(SRC)file_handler.c

linter.o: $(SRC)linter.c $(HED)mainlib.h
	$(COM) -c $(SRC)linter.c

tokenizer.o: $(SRC)tokenizer.c $(HED)mainlib.h
	$(COM) -c $(SRC)tokenizer.c

compiler.o: $(SRC)compiler.c $(HED)mainlib.h $(HED)map.h
	$(COM) -c $(SRC)compiler.c

interpreter.o: $(SRC)interpreter.c $(HED)mainlib.h
	$(COM) -c $(SRC)interpreter.c

util.o: $(SRC)util.c $(HED)mainlib.h
	$(COM) -c $(SRC)util.c

clean:
	$(COMMAND) *.o
