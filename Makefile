CC		:= gcc
# CFLAGS	:= -w 

BIN		:= bin
SRC		:= src
INCLUDE	:= src

EXECUTABLE	:= trab2
SOURCEDIRS	:= $(shell find $(SRC) -type d)
INCLUDEDIRS	:= $(shell find $(INCLUDE) -type d)

ARGS  := 
ARGS0 := ./input/0.txt
SAIDA := saida.txt

VALGRIND	:= 

CINCLUDES	:= $(patsubst %,-I%, $(INCLUDEDIRS:%/=%))
SOURCES		:= $(wildcard $(patsubst %,%/*.c, $(SOURCEDIRS)))
OBJECTS		:= $(SOURCES:.c=.o)

all: clean $(EXECUTABLE)

.PHONY: clean
clean:
	-$(RM) $(OBJECTS)

run: 
	./$(EXECUTABLE) $(ARGS) $(SAIDA)

run0: 
	./$(EXECUTABLE) $(ARGS0) $(SAIDA)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(CFLAGS) $(CINCLUDES) $^ -o $@ $(LIBRARIES) -lm

val: 
	valgrind ./$(EXECUTABLE) $(ARGS) $(SAIDA)

val0: 
	valgrind ./$(EXECUTABLE) $(ARGS0) $(SAIDA)
	
full: 
	- valgrind -v --leak-check=full ./$(EXECUTABLE) $(N)
