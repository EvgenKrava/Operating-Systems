#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <malloc.h>

int main (int argv, char **argc) {
	printf ("Start the program\n");
	char *commands = malloc(sizeof(char) * 256);
	for(int i = 1; i < argv; ++i){
		commands = strcat(commands, " ");
		commands = strcat(commands, argc[i]);
	}
	printf("Exit code: %d\n", system(commands));
	free(commands);
	return EXIT_SUCCESS;
}
