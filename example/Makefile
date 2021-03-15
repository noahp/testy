# Example makefile
.SILENT:

TESTY_ROOT_DIR = ..
CC ?= gcc

.PHONY: all

all: main test

C_SRCS = $(wildcard *.c)

main: $(C_SRCS)
	gcc -I $(TESTY_ROOT_DIR) $^ -o $@

test: $(C_SRCS)
	CC="$(CC) -I$(abspath .)" $(TESTY_ROOT_DIR)/testy.py $^
