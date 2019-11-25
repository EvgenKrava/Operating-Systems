#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

void* child_thread(void* n){
    pthread_setcancelstate(PTHREAD_CANCEL_DISABLE, NULL);
    for (int i = 0; i < *((int*)n) * 2; ++i) {
        printf("Child thread Iteration %d\n", i);
        sleep(1);
    }
}

int main(int argc, char** argv){
    if (argc < 2) 
		return 0;
    int n = atoi(argv[1]);
    void* result;
    pthread_t child;
    pthread_attr_t attr;
    if (pthread_attr_init(&attr) != 0) {
        fprintf(stdout, "Can't init attributes\n");
	}
    if (pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE) != 0) {
        fprintf(stdout, "Can't detach\n");
	}
    if (pthread_create(&child, &attr, &child_thread, &n) != 0) {
        fprintf(stdout, "Can't create thread!\n");
	}
    sleep(n);
    pthread_cancel(child);
    pthread_join(child, &result);
    if (result == PTHREAD_CANCELED) {
        fprintf(stdout, "Child thread canceled!\n");
    } else { 
		fprintf(stdout, "Child thread finished normal!\n");
	}  
	return 0;
}
