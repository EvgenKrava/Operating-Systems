#include <stdio.h>
#include <stdlib.h>
void callback1(void) { printf("Callback1 invoked\n"); }
void callback2(void) { printf("Callback2 invoked\n"); }
void callback3(void) { printf("Callback3 invoked\n"); }

int main(int argc, char **argv) {
	const struct option long_opt[] = {
		{"file", 1, 0, 'f'},
		{"number", 1, 0, 'n'},
		{NULL,0,NULL,0}
	};

	int n = 0;	
	char c;
	while ((c = getopt_long(argc, argv, "f:n:", long_opt, NULL)) != -1) {
		switch(c){
			case 'f':
				buffer = atoi(optarg);
				fprintf(stderr, "Buffer size: %d\n", buffer);
				break;
			case 'n':
				printf("For exit input 'stop'\n");
				break;
			case '?':
				fprintf(stderr, "%s\n", "Unknown option");
				break;
		}
	}

	for(int i = 0; i < n; ++i) {
	
	}
	char *command;
	printf("Callback1 registration\n");
	if(atexit(callback1)) fprintf(stderr, "Callback1 registration failed\n");
	printf("Callback2 registration\n");
	if(atexit(callback2)) fprintf(stderr, "Callback2 registration failed\n");
	printf("Callback3 registration\n");
	if(atexit(callback3)) fprintf(stderr, "Callback3 registration failed\n");
	return EXIT_SUCCESS; /* exit(0); */
}
