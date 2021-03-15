# Example makefile
.SILENT:

TESTY_ROOT_DIR = ..

.PHONY: all

all: test

C_SRCS = $(wildcard *.c)


test: $(C_SRCS)
	CC="gcc -I$(abspath .)" $(TESTY_ROOT_DIR)/testy.py $^
