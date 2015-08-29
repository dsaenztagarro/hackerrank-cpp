vpath %.c src
vpath %.h include
vpath %.o build

SOURCE_DIR := src
TEST_DIR := test
OUTPUT_DIR := build

SOURCES = $(shell find $(SOURCE_DIR)/ -name *.c | sed 's/src\/\///')
DEPS = $(subst .c,.o, $(SOURCES))
OBJECTS = $(addprefix $(OUTPUT_DIR)/, $(DEPS))
TEST = $(shell find $(TEST_DIR)/ -name *.c | sed 's/test\/\///')
DEPS_TEST = $(subst .c,.o, $(TEST))
OBJECTS_TEST=$(shell echo "$(OBJECTS)" | sed 's/$(OUTPUT_DIR)\/main\.o//')

OUTPUT_OPTION = -o $(OUTPUT_DIR)/$@

CC = cc
RM = rm -rf

COMPILE_FLAGS = -std=c99 -Wall -Wextra -g
LANGUAGE_FLAGS = -ansi --pedantic
CFLAGS = $(COMPILE_FLAGS) $(LANGUAGE_FLAGS)

INCLUDES=-I /usr/include -I include -lcheck

LINK.o = $(CC) $(COMPILE_FLAGS) $(INCLUDES)
COMPILE.c = $(CC) $(CFLAGS) $(INCLUDES) -c

main: $(DEPS)
	$(LINK.o) $(OBJECTS) -o bin/$@

main.o: main.c graph.o
	$(COMPILE.c) $< $(OUTPUT_OPTION)

graph.o: graph.c
	$(COMPILE.c) $< $(OUTPUT_OPTION)

.PHONY: clean
clean:
	mkdir -p bin && $(RM) bin/*
	mkdir -p build && $(RM) build/*

.PHONY: check
check: $(DEPS_TEST) $(DEPS)
	$(info $(OBJECTS_TEST))
	$(info $(DEPS_TEST))
	$(LINK.o) build/check_queue.o $(OBJECTS_TEST) -o bin/check_queue

check_queue.o: test/check_queue.c $(DEPS)
	$(COMPILE.c) $< $(OUTPUT_OPTION)


.PHONY: echo
echo:
	$(info $(SOURCES))
	$(info $(SOURCES))
	$(info $(OBJECTS))




