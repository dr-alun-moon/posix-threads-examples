/* A multi threadded example
 * count characters in a file
 *
 * Dr Alun Moon
 */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <pthread.h>

/* find the size of the file */
long fsize(FILE *fh)
{
	long size;
	fseek(fh, 0, SEEK_END);
	size = ftell(fh);
	fseek(fh, 0, SEEK_SET);
	return size;
}


/* A progress meter */
int   count;
int   maxch;
char *fname;
#define metersize 50
char meterbar[metersize];
void *progress(void *arg)
{
	int pc, c;
	for(c=0;c<metersize;c++) meterbar[c]=' ';
	printf("\e[H\e[J"); /* cursor to top left, clear screen */
	for(c=0 ; c<3 ; c++) printf(" %s   \n",meterbar);
	while(1){
		pc = 100*count/maxch;
		meterbar[pc*metersize/100]='=';
		printf("\e[H"); /* cursor to top left */
		printf("File: %s\n",fname);
		printf("Characters read: %7d/%7d\n", count, maxch);
		printf("[%*s] %3d%%\n",metersize,meterbar,pc);
		fflush(stdout);
	}
	return NULL;
}

/* read and process character counts */
int freqtable[256];
void *countcharacters(void *arg)
{
	FILE *source = (FILE*)arg;
	int c,p;
	for( c=0 ; c<256 ; c++) freqtable[c]=0;

	while( (c=fgetc(source)) != EOF ) {
		freqtable[c]++;
		count++;
		for(p=0;p<1000;p++); /* need a little pause to make it run in a noticable time */
	}
	return NULL;
}
void printfreq(void)
{
	int c;
	putchar('\n');
	for( c=' ' ; c<0x7f ; c++ ) {
		printf("%c :%6d    ",c,freqtable[c]);
		if( (c%8)==7 ) putchar('\n');
	}
	putchar('\n');
}

int main ( int argc, char *argv[] )
{
	int n;
	FILE *handle;
	pthread_t meter, counter;
	if(argc<2) fprintf(stderr,"usage: charfrequency <filename>\n");
	fname = argv[1];
	handle = fopen(fname, "r");
	if(!handle) exit(EXIT_FAILURE);

	maxch = fsize( handle );
	count = 0;
	
	pthread_create(&meter, NULL, progress, NULL);
	pthread_create(&counter, NULL, countcharacters, (void*)handle);

	pthread_join(counter, NULL); /* wait for counting to finish */
	pthread_cancel(meter);

	fflush(stdout);
	printfreq();
}

