vpath %.c src
vpath %.h include
vpath %.o build

SOURCE_DIR := src
OUTPUT_DIR := build

SOURCES = $(shell find $(SOURCE_DIR)/ -name *.c | sed 's/src\/\///')
DEPENDENCIES = $(subst .c,.o, $(SOURCES))
OBJECTS = $(addprefix $(OUTPUT_DIR)/, $(DEPENDENCIES))

OUTPUT_OPTION = -o $(OUTPUT_DIR)/$@

CC=cc
# General compiler flags
COMPILE_FLAGS = -std=c99 -Wall -Wextra -g

CFLAGS = $(COMPILE_FLAGS) -ansi --pedantic

INCLUDES=-I /usr/include -I include

COMPILE.c = $(CC) $(CFLAGS) $(INCLUDES) -c

main: $(DEPENDENCIES)
	$(CC) $(COMPILE_FLAGS) $(INCLUDES) $(OBJECTS) -o bin/$@

main.o: main.c graph.o
	$(COMPILE.c) $< $(OUTPUT_OPTION)

graph.o: graph.c
	$(COMPILE.c) $< $(OUTPUT_OPTION)

.PHONY: clean
clean:
	mkdir -p bin && rm -rf bin/*
	mkdir -p build && rm -rf build/*

.PHONY: echo
echo:
	$(info $(SOURCES))
	$(info $(OBJECTS))
