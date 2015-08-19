vpath %.c src
vpath %.h include
vpath %.o build

SOURCE_DIR := src
OUTPUT_DIR := build

OUTPUT_OPTION = -o $(OUTPUT_DIR)/$@

CC=cc
# General compiler flags
COMPILE_FLAGS = -std=c99 -Wall -Wextra -g

CFLAGS = $(COMPILE_FLAGS) -ansi --pedantic

INCLUDES=-I /usr/include -I include

COMPILE.c = $(CC) $(CFLAGS) $(INCLUDES) -c

main: main.o graph.o
	$(CC) $(COMPILE_FLAGS) $(INCLUDES) build/main.o build/graph.o -o bin/$@

main.o: main.c graph.o
	$(COMPILE.c) $< $(OUTPUT_OPTION)

graph.o: graph.c
	$(COMPILE.c) $< $(OUTPUT_OPTION)

.PHONY: clean
clean:
	mkdir -p bin && rm -rf bin/*
	mkdir -p build && rm -rf build/*
