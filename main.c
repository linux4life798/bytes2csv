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

#define TRUE  1
#define FALSE 0

void usage(FILE *out)
{
	fprintf(out, "Reads a binary and presents the bytes in as hex, ascii chars, and/or natural numbers.\n");
	fprintf(out, "Usage: bytes2csv [-a] [-n] [-h] [input-file]\n");
	fprintf(out, "\t-a: insert row of ascii\n");
	fprintf(out, "\t-n: insert row of numbers\n");
	fprintf(out, "\t-h: help\n");
	fprintf(out, "\tinput-file: binary char file to convert\n");
	fprintf(out, "note: also supports piping. Eg. cat binfile | bytes2csv\n");
}

extern char *optarg;
extern int optind, opterr, optopt;
/* int getopt(int argc, char * const argv[], const char *optstring); */

int main(int argc, char *argv[]) {
	int ascii = FALSE, numbs = FALSE;
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
			case 'h':
			case '?':
				usage(stderr);
				exit(1);
				break;
		}
	}

	/* is input file an argument or piped in */
	if(optind < argc)
	{
		input = fopen(argv[optind],"r");
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
	printf("%.2X", fgetc(input));
	while(!feof(input))
		printf(",%.2X", fgetc(input));

	/* print ascii chars row if -a flag */
	if(ascii)
	{
		/* dose not show col value if cha is not visible */
		char c;
		putchar('\n');
		rewind(input);
		c = fgetc(input); 
		if((' ' <= c) && (c <= '~'))
			printf("%c",c);
		while(!feof(input)) {
			c = fgetc(input);
			if((' ' <= c) && (c <= '~'))
				printf(",%c",c);
		}
	}
	/* print numbs row if -n flag */
	if(numbs)
	{
		putchar('\n');
		rewind(input);
		printf("%3u", fgetc(input));
		while(!feof(input))
			printf(",%3u", fgetc(input));
	}

	putchar('\n');

	if(input != stdout)
		fclose(input);

	return 0;
}
