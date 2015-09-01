vpath %.o ./build

APP_DIR := app
LIB_DIR := lib
TEST_DIR := test
OUTPUT_DIR := build

SOURCES = $(shell find $(LIB_DIR) -name *.c)
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

INCLUDES = -I /usr/include -I include
TEST_INCLUDES = -lcheck

LINK.o = $(CC) $(COMPILE_FLAGS) $(INCLUDES)
COMPILE.c = $(CC) $(CFLAGS) $(INCLUDES) -c

main: app/main.o $(DEPS)
	$(LINK.o) build/app/main.o $(OBJECTS) -o bin/$@

app/%.o: app/%.c graph.o
	@mkdir -p $(shell dirname build/$<)
	$(COMPILE.c) $< $(OUTPUT_OPTION)

%.o: %.c
	$(info $@)
	$(info $<)
	@mkdir -p $(shell dirname build/$<)
	$(COMPILE.c) $< $(OUTPUT_OPTION)

.PHONY: clean
clean:
	$(RM) bin/*
	$(RM) build/*

.PHONY: check
check: $(DEPS_TEST) $(DEPS)
	$(info $(OBJECTS_TEST))
	$(info $(DEPS_TEST))
	# $(LINK.o) build/check_queue.o $(OBJECTS_TEST) -o bin/check_queue

check_queue.o: test/check_queue.c $(DEPS)
	$(COMPILE.c) $< $(OUTPUT_OPTION)

.PHONY: sources
sources:
	$(info $(SOURCES))
