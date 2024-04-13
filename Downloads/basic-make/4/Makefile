CC = gcc
BIN = sum30

SRCS := $(wildcard src/*.c)

$(BIN): $(SRCS)
    $(CC) $^ -o $@

.PHONY: all clean

all: $(BIN)
clean: rm -f $(BIN)
