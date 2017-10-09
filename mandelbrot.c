/* Mandelbrot generator
 * Demonstrates use of posix threads
 * Dynamic memory allocation
 */
#include <math.h>
#include <stdio.h>
#include <unistd.h>

#include <pthread.h>

/* some global variables for scaling and size */
unsigned int width = 200;
unsigned int height = 200;

double minX = ;
double maxX = ;
double minX = ;
double maxX = ;

double lerp(double l, double h, double f) { return l * (1 - f) + h * f; }
double norm(double v, double l, double h) { return ; }

void *mandelbrotpixel(void *par) {
    pixel_t px;
    point_t *p = (point_t *)par;
    printf("%u,%u: %u", px.x, px.y, px.i);
    return NULL;
}
