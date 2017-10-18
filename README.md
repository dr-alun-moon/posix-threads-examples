# POSIX Threads Example Programs
These are some example programs that make use of POSIX threads.

## To use:
The simple version is just to use `make`

## The Mandelbrot set
The program `mandelbrot.c` creates a mandelbrot set by splitting the image into tiles and then running one thread per tile.

The output is designed to be piped into ImageMagick's convert program.
As this can cope with the pixels given in any order, the threads can write to standard-output, with worrying about how the data gets interleaved.

   ```bash
   make color-mandelbrot.png
   ```

### Shell scripts
As an example of shell-script use, there are two scripts in parallel with `make`.  The script `ckconv` checks if ImageMagick is installed, it not uses `apt` to install the imagemagick package.

`mkmandelbrot` compiles the c-code if needed and creates the mandelbrot image.

### Makefile
The makefile is a (better) option as make can handle a lot of the dependencies much better that a shell script can.

## Character frequency counter
This example reads in text from a file and counts the numbers of each character found in it.
The program has two threads, one does the counting and the other updates the display and progress meter.
They have shared global variables that are used for the comminication.

## Sums numbers
`summation.c` is a simple partition of adding up numbers into sections each handled by one thread.

## Thread Parameters
The `threadparam.c` program demonstrates how to pass parameters to threads using pointers-to-structures, and how to recover the results.

