# Example makefile

.SILENT:
.PHONY: all

all: main

C_SRCS = $(wildcard *.c)

main: $(C_SRCS)
	gcc -I ../ $^ -o $@
