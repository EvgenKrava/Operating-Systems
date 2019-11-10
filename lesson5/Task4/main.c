#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>

void exit_handler(void){
	printf("Wait 3 seconds...\n");
	system("sleep 3");
}

int main(int argc, char **argv){
	const struct option long_opt[] = {
		{"help", 0, 0, 'h'},
		{"buffer", 1, 0, 'b'},
		{NULL,0,NULL,0}
	};
	char *command;
	int buffer = 127;
	char c;
	while ((c = getopt_long(argc, argv, "b:h", long_opt, NULL)) != -1){
		switch( c ){
			case 'b':
				buffer = atoi(optarg);
				fprintf(stderr, "Buffer size: %d\n", buffer);
				break;
			case 'h':
				printf("For exit input 'stop'\n");
				break;
			case '?':
				fprintf(stderr, "%s\n", "Unknown option");
				break;
		}
	}
	
	command = malloc(buffer * sizeof(char));
	atexit(exit_handler);
	char *user = getenv("USER");
	printf("Hello %s\n", user);
	while(1){
		printf("[%s]$ ", user);
		fgets(command, buffer, stdin);
		if(strcmp(command, "stop") == 10){
			break;
		}
		system(command);
	}
	return EXIT_SUCCESS;
}
