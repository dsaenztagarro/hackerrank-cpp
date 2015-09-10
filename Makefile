vpath %.o ./build

APP_DIR := app
LIB_DIR := lib
TEST_DIR := test
OUTPUT_DIR := build

SOURCES = $(shell find $(LIB_DIR) -name *.c)
DEPS = $(subst .c,.o, $(SOURCES))
OBJECTS = $(addprefix $(OUTPUT_DIR)/, $(DEPS))
SOURCES_TEST = $(shell find $(TEST_DIR) -name *.c)
DEPS_TEST = $(subst .c,.o, $(SOURCES_TEST))
OBJECTS_TEST=$(shell echo "$(OBJECTS)" | sed 's/$(OUTPUT_DIR)\/main\.o//')

CHECK_FLAGS = $(shell pkg-config --cflags --libs check)

# ANSI Escape codes
NO_COLOR=\033[0m
OK_COLOR=\033[32;01m
ERROR_COLOR=\033[31;01m

AWK_CMD = awk '{ printf "%s %-30s %-10s\n",$$1, $$2, $$3; }'
AWK_ACTION_CMD = awk '{ printf "%-40s %-10s\n",$$1, $$2; }'
OK_STRING=$(OK_COLOR)[OK]$(NO_COLOR)
ERROR_STRING=$(ERROR_COLOR)[ERRORS]$(NO_COLOR)

define log-compile
	@if [ $$? -eq 0 ]; \
	then \
		echo "Compiling $< $(OK_STRING)" | $(AWK_CMD); \
	else \
		echo "Compiling $@ $(ERROR_STRING)" | $(AWK_CMD); \
	fi;
endef

define log-action
	@if [ $$? -eq 0 ]; \
	then \
		echo "$1 $(OK_STRING)" | $(AWK_ACTION_CMD); \
	else \
		echo "$1 $(ERROR_STRING)" | $(AWK_ACTION_CMD); \
	fi;
endef

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

.PHONY: all
all: compile check

compile: app/main.o $(DEPS)
	@mkdir -p bin
	@$(LINK.o) build/app/main.o $(OBJECTS) -o bin/main
	$(call log-action, "Linking", "bin/main")

%.o: %.c
	@mkdir -p $(shell dirname build/$<)
	@$(COMPILE.c) $< $(OUTPUT_OPTION)
	$(call log-compile)

.PHONY: clean
clean:
	@$(RM) bin/
	@$(RM) build/
	$(call log-action, "Cleaning")

.PHONY: check
check: app/check_all.o $(DEPS_TEST) compile
	$(call log-action, "Checking")
	@$(LINK.o) build/app/check_all.o build/test/check_graph.o build/test/check_queue.o $(OBJECTS_TEST) -o bin/check_all $(CHECK_FLAGS)
	@./bin/check_all

.PHONY: sources
sources:
	$(info $(SOURCES))
