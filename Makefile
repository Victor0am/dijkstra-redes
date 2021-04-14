# Grupo: 
# Beatriz Matias Santana Maia: 2019107651
# Henrique Paulino Cruz:
# Victor Aguiar Marques:

CC		:= gcc
CFLAGS	:= 

BIN		:= bin
SRC		:= src
INCLUDE	:= src

EXECUTABLE	:= trab2
SOURCEDIRS	:= $(shell find $(SRC) -type d)
INCLUDEDIRS	:= $(shell find $(INCLUDE) -type d)

ARGS    := 
SAIDA   := saida.txt

# Argumentos utilizados para testar codigo

# Caso teste do pdf
ARGS0   := ./input/0.txt 
# Caso de 10 nos
ARGS10  := ./input/1.txt
# Caso de 100 nos
ARGS100 := ./input/2.txt
# Caso de 1000 nos
ARGS1K  := ./input/3.txt
# Caso de 10000 nos
ARGS10K := ./input/4.txt

VALGRIND	:= 

CINCLUDES	:= $(patsubst %,-I%, $(INCLUDEDIRS:%/=%))
SOURCES		:= $(wildcard $(patsubst %,%/*.c, $(SOURCEDIRS)))
OBJECTS		:= $(SOURCES:.c=.o)

all: clean $(EXECUTABLE)

.PHONY: clean
clean:
	-$(RM) $(OBJECTS)

# Comandos para executar
run: 
	# ./$(EXECUTABLE) $(ARGS) ./output/
	echo "run0 run10 run100 run1k run10k"

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
	$(CC) $(CFLAGS) $(CINCLUDES) $^ -o $@ $(LIBRARIES)

# Comandos para executar com valgrind
val: 
	# valgrind ./$(EXECUTABLE) $(ARGS) $(SAIDA)
	echo "val0 val10 val100 val1k val10k"

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