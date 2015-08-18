vpath %.c src
vpath %.h include
vpath %.o build
BIN_PATH=./bin
BUILD_PATH=./build

CC=cc
OUTPUT_OPTION = -o $(BUILD_PATH)/$@
CFLAGS=-std=c99 -Wall -Wextra -Werror -ansi --pedantic
INCLUDES=-I /usr/include -I include

COMPILE.c = $(CC) $(CFLAGS) $(INCLUDES) $(CPPFLAGS) $(TARGET_ARCH) -c

main: main.c graph.o
	$(CC) $(CFLAGS) $(INCLUDES) $(CPPFLAGS) $(TARGET_ARCH) $< -o $(BIN_PATH)/$@

graph.o: graph.c graph.h
	$(COMPILE.c) $< $(OUTPUT_OPTION)

test: test.o clean
	$(CC) $(CFLAGS) $< $(OUTPUT_OPTION) $(LDFLAGS)

test.o: test.c
	$(COMPILE.c) $<

clean:
	mkdir -p bin && rm -rf bin/*
	mkdir -p build && rm -rf build/*
