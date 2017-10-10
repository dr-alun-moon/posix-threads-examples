# makefie
CFLAGS=-g -pthread
LDLIBS=-lm

all: binaries images

binaries: fork_ex thread_ex summation mandelbrot
images: colour-mandelbrot.png

mandelbrot.png: PATH:=.:$(PATH)
mandelbrot.png: mandelbrot 
	mandelbrot | convert txt:- mandelbrot.png

# These two need ImageMagick installed
# to install
# sudo apt -q -y install imagemagick
colourmap.png: 
	convert xc:black xc:red xc:yellow xc:green1 \
		xc:cyan xc:blue xc:black +append \
		-filter Cubic -resize 256x1\! colourmap.png 
colour-mandelbrot.png: mandelbrot.png colourmap.png
	convert mandelbrot.png \( colourmap.png \) -clut colour-mandelbrot.png

.PHONY: clean
clean:
	rm -f thread_ex fork_ex summation mandelbrot
	rm -f mandelbrot.png colourmap.png colour-mandelbrot.png
