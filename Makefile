CC		:= gcc
CFLAGS	:= 

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
SAIDA := saida/

VALGRIND	:= 

CINCLUDES	:= $(patsubst %,-I%, $(INCLUDEDIRS:%/=%))
SOURCES		:= $(wildcard $(patsubst %,%/*.c, $(SOURCEDIRS)))
OBJECTS		:= $(SOURCES:.c=.o)

all: clean $(EXECUTABLE)

.PHONY: clean
clean:
	-$(RM) $(OBJECTS)

run: 
	./$(EXECUTABLE) $(ARGS) ./output/

run0: 
	./$(EXECUTABLE) $(ARGS0) ./output/0.txt

run10:
	./$(EXECUTABLE) $(ARGS10) ./output/1.txt

run100:
	./$(EXECUTABLE) $(ARGS100) ./output/2.txt

run1k:
	./$(EXECUTABLE) $(ARGS1K) ./output/3.txt

run10k:
	./$(EXECUTABLE) $(ARGS10K) ./output/4.txt
	
$(EXECUTABLE): $(OBJECTS)
	$(CC) $(CFLAGS) $(CINCLUDES) $^ -o $@ $(LIBRARIES) -lm

val: 
	valgrind ./$(EXECUTABLE) $(ARGS) $(SAIDA)

val0: 
	valgrind ./$(EXECUTABLE) $(ARGS0) ./output/0.txt

val10:
	valgrind ./$(EXECUTABLE) $(ARGS10) ./output/1.txt

val100:
	valgrind ./$(EXECUTABLE) $(ARGS100) ./output/2.txt

val1k:
	valgrind ./$(EXECUTABLE) $(ARGS1K) ./output/3.txt

val10k:
	valgrind ./$(EXECUTABLE) $(ARGS10K) ./output/4.txt
	
full: 
	- valgrind -v --leak-check=full ./$(EXECUTABLE) $(N)
