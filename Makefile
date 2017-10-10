# makefie
CFLAGS=-g -pthread
LDLIBS=-lm

all: binaries mandelbrot.png

binaries: fork_ex thread_ex summation mandelbrot


mandelbrot.png: PATH:=.:$(PATH)
mandelbrot.png: mandelbrot 
	mandelbrot | convert txt:- mandelbrot.png

.PHONY: clean
clean:
	rm -f thread_ex fork_ex summation mandelbrot
	rm -f mandelbrot.png 
