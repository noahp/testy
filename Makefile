.SILENT:
.PHONY: all

all: testy
	./$^

testy: $(wildcard *.c)
	gcc $^ -o $@
