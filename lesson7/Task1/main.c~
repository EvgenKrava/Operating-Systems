#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#define SECONDSCOUNT 1


void *thread_function(void *arg) {
	for(int i = 1; i <= 10; ++i) {
		fprintf(stdout, "Child Thread. Iteration: %d\n", i);
		sleep(SECONDSCOUNT);
	}
	return NULL;
}

int main(int argv, char **argc){
	pthread_t t;
	int result;
	result = pthread_create(&t, NULL, &thread_function, NULL);
	if (result != 0) {
		fprintf(stderr, "Error\n");
		return 1;
	}
	for(int i = 1; i <= 10; ++i) {
		fprintf(stdout, "Main Thread. Iteration: %d\n", i);
		sleep(SECONDSCOUNT);
	}
	return 0;
}
