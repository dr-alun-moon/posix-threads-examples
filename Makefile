# makefie
all: binaries mandelbrot.png

binaries: fork_ex thread_ex summation mandelbrot

% : %.c
	cc -g -pthread -o $* $<

mandelbrot.png: mandelbrot
	PATH=.:$(PATH) mandelbrot | convert txt:- mandelbrot.png

.PHONY: clean
clean:
	rm -f thread_ex
	rm -f fork_ex
	rm -f summation
	rm -f mandelbrot
