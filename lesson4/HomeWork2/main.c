#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include "environ.h"

int main(int argc, char **argv) {
	int c;
	const struct option long_opt[] = {
						{"help", 0, 0, 'h'},
						{"info", 1, 0, 'i'},
						{"set" , 1, 0, 's'},
						{"assign", 1, 0, 'a'},
						{"value", 1, 0, 'v'},
						{"del", 1, 0, 'd'},
						{"clear", 0, 0, 'c'},
						{NULL,0,NULL,0}
	};
	while ((c = getopt_long(argc, argv, "i:s:a:v:d:ch", long_opt, NULL)) != -1){
	switch( c ){
		case 'h':
			usage(argv[0]);
			return(-1);
		case 'c':
			printf("option 'c' selected, filename: %s\n",          );
			return(1);
		case '?':
			fprintf(stderr, "%s\n", "Unknown option");
			return 2;
		}
	}
	return 0;
}
