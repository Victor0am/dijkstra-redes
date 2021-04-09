CC		:= gcc
# CFLAGS	:= -w 

BIN		:= bin
SRC		:= src
INCLUDE	:= src

EXECUTABLE	:= trab2
SOURCEDIRS	:= $(shell find $(SRC) -type d)
INCLUDEDIRS	:= $(shell find $(INCLUDE) -type d)

ARGS    := 
ARGS0   := ./input/0.txt

ARGS10  := ./input/1.txt
ARGS100 := ./input/2.txt
ARGS1K  := ./input/3.txt
ARGS10K := ./input/4.txt
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

run10:
	./$(EXECUTABLE) $(ARGS10) $(SAIDA)

run100:
	./$(EXECUTABLE) $(ARGS100) $(SAIDA)

run1k:
	./$(EXECUTABLE) $(ARGS1K) $(SAIDA)

run10k:
	./$(EXECUTABLE) $(ARGS10K) $(SAIDA)
	
$(EXECUTABLE): $(OBJECTS)
	$(CC) $(CFLAGS) $(CINCLUDES) $^ -o $@ $(LIBRARIES) -lm

val: 
	valgrind ./$(EXECUTABLE) $(ARGS) $(SAIDA)

val0: 
	valgrind ./$(EXECUTABLE) $(ARGS0) $(SAIDA)

val10:
	valgrind ./$(EXECUTABLE) $(ARGS10) $(SAIDA)

val100:
	valgrind ./$(EXECUTABLE) $(ARGS100) $(SAIDA)

val1k:
	valgrind ./$(EXECUTABLE) $(ARGS1K) $(SAIDA)

val10k:
	valgrind ./$(EXECUTABLE) $(ARGS10K) $(SAIDA)
	
full: 
	- valgrind -v --leak-check=full ./$(EXECUTABLE) $(N)
