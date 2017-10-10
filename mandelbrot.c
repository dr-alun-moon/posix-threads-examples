/* Mandelbrot generator
 * Demonstrates use of posix threads
 * Dynamic memory allocation
 */
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <pthread.h>

/* some global variables for scaling and size */
unsigned int  width = 1024;
unsigned int height = 1024;
unsigned int  depth = 255;

double minX = -1;
double maxX = -0.9;
double minY =  0.24;
double maxY =  0.34;
double epsilon = 0.0001;

unsigned int cuts=4;

/* type for passing tile information to thread */
typedef struct {
    unsigned int x_min, x_max;
    unsigned int y_min, y_max;
} tile_t;

/* math utilities (based on Processing.org) */
double lerp(double l, double h, double f) { return l*(1-f) + h*f; }
double norm(double v, double l, double h) { return (v-l)/(h-l); }
double map(double v, double l1, double h1, double l2, double h2) {
    return lerp(l2, h2, norm(v, l1, h1));
}

/* calculate number of steps for point to escape */
unsigned int mandelbrot_escape(double x0, double y0, unsigned int limit) {
    /* see http://paulbourke.net/fractals/mandelbrot/
     * for description and notes
     */
    double x=0, y=0, xnew, ynew;
    unsigned int n;
    for ( n=0 ; n<limit ; n++ ) {
		xnew = x*x - y*y + x0;
		ynew = 2*x*y + y0;
		if ( (xnew*xnew + ynew*ynew) > 4.0 ) break;
		if ( fabs(xnew-x)<epsilon && fabs(ynew-y)<epsilon ) {
			n = limit;
			break;
		}
		x = xnew;
		y = ynew;
    }
    return n;
}

/* Worker thread for a tile */
void *mandelbrot_tile(void *par) {
    tile_t *tile = (tile_t *)par;
   unsigned int x, y;
    for (x = tile->x_min; x < tile->x_max; x++) {
		for (y = tile->y_min; y < tile->y_max; y++) {
	    	double xx = map(x, 0, width, minX, maxX);
	    	double yy = map(y, 0, height, minY, maxY);
	    	unsigned int m = mandelbrot_escape(xx, yy, depth);
	    	/* see http://www.imagemagick.org/Usage/files/#txt for format */
	    	printf("%u,%u: (%u)\n", x, y, m);
		}
    }
    return par;
}

int main(int argc, char *argv[]) {
	unsigned int slices = pow(2,cuts);
	int Ntiles = (slices)*(slices);
	int Twide  = width/(slices);
	int Thigh  = height/(slices);
	int tx,ty;
	
	/* write image format header 
	 * see http://www.imagemagick.org/Usage/files/#txt 
	 */
	printf("# ImageMagick pixel enumeration: %d,%d,%d,gray\n",
		   	width,height, depth);
	/* Create and start threads */
	pthread_t Worker[Ntiles];
	int t=0, c;
	for( tx=0 ; tx<width ; tx+=Twide ) {
		for( ty=0 ; ty<height ; ty+=Thigh ) {
			tile_t *tile = malloc( sizeof(tile_t));
			tile->x_min = tx;
			tile->x_max = tx+Twide;
			tile->y_min = ty;
			tile->y_max = ty+Thigh;
			c = pthread_create(Worker+t, NULL, mandelbrot_tile, tile);
			if(c) fprintf(stderr,"error on thread %d\n",t);
			t++;
		}
	}
	for( t=0 ; t<Ntiles ; t++ ){
		void *retval;
		pthread_join(Worker[t],&retval);
		free(retval);
	}
}
