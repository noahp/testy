# Example makefile
.SILENT:

TESTY_ROOT_DIR = ..

.PHONY: all

all: main test

C_SRCS = $(wildcard *.c)

main: $(C_SRCS)
	gcc -I ../ $^ -o $@

test: $(C_SRCS)
	CC="gcc -I$(abspath .)" $(TESTY_ROOT_DIR)/testy.py $^
