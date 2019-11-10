#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int i = 0;

void callback(void) {
	system("sleep 1");
	printf("Handler = %d\n", ++i); 
}

int main(int argc, char **argv) {
	for(int j = 0; j < atoi(argv[1]); ++j){
		atexit(callback);
	}	
	return EXIT_SUCCESS;
}
