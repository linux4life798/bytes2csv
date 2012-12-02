/**
 * Reads a binary file and outputs a Comma Separated Value(CSV) 
 * 	list of it's chars represented in different ways.
 *
 * @author Craig Hesling
 * @date Dec 2, 2012
 */

#include <unistd.h> /* getopt */
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h> /* strerr() */

#define TRUE 1
#define FALSE 0

void usage(FILE *out)
{
	fprintf(out, "Reads a binary and presents the bytes in ways\n");
	fprintf(out, "Usage: bytes2csv [-a] [-n] [-h] [input]\n");
	fprintf(out, "\t-a: insert row of ascii\n");
	fprintf(out, "\t-n: insert row of numbers\n");
	fprintf(out, "\t-h: help\n");
	fprintf(out, "\t-h: help\n");
}

extern char *optarg;
extern int optind, opterr, optopt;
/* int getopt(int argc, char * const argv[], const char *optstring); */

int main(int argc, char *argv[]) {
	int ascii = FALSE, numbs = FALSE;
	char *cmdin = NULL;
	int opt = 0;
	FILE *input = NULL;

	while((opt = getopt(argc, argv, "anh")) != -1){
		switch (opt){
			case 'a':
				ascii = TRUE;
				break;
			case 'n':
				numbs = TRUE;
				break;
			case '1':
				cmdin = optarg;
				break;
			case 'h':
			case '?':
				usage(stderr);
				exit(1);
				break;
		}
	}

	/* is input file an argument or piped in */
	if(cmdin)
	{
		input = fopen(optarg,"r");
		if(!input){
			fprintf(stderr, "Error opening %s - %s\n", optarg, strerror(errno));
			exit(1);
		}
	}
	else {
		printf("Reading input file\n\n");
		input = stdin;
	}

	/* print hex chars row 1 */
	printf("%X", fgetc(input));
	while(!feof(input))
		printf(",%X", fgetc(input));

	/* print ascii chars row if -a flag */
	if(ascii)
	{
		rewind(input);
		printf("%c", fgetc(input));
		while(!feof(input))
			printf(",%c", fgetc(input));
	}
	/* print numbs row if -n flag */
	if(numbs)
	{
		rewind(input);
		printf("%u", fgetc(input));
		while(!feof(input))
			printf(",%u", fgetc(input));
	}

	if(input != stdout)
		fclose(input);

	return 0;
}
