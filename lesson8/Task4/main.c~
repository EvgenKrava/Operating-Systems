#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

#define MAX_PI 1000000



void* child_thread(void* n) {
    pthread_setcancelstate(PTHREAD_CANCEL_ENABLE, NULL);
    pthread_setcanceltype(PTHREAD_CANCEL_DEFERRED, NULL);
    char sign = 1;
    double a = 1,b = 1;
    double* pi = (double*)malloc(sizeof(double));
    for (int i = 0; i < MAX_PI; ++i) {
        pthread_setcancelstate(PTHREAD_CANCEL_DISABLE, NULL);
        *pi += sign * (a / b) * 4;
        fprintf(stdout, "Pi: %lf\n", *pi);
        b += 2;
        sign *= -1;
		//sleep(1);
        pthread_setcancelstate(PTHREAD_CANCEL_ENABLE, NULL);
        pthread_setcanceltype(PTHREAD_CANCEL_DEFERRED, NULL);
        pthread_testcancel();
    }
    return pi;
}

int main(int argc, char** argv){
    if(argc < 2)
		return 0;
    int n = atoi(argv[1]);
    void* result;
    pthread_t child;
    pthread_attr_t attr;
    if (pthread_attr_init(&attr) != 0) {
        fprintf(stdout,"Error while init attributes\n");
	}
    if (pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE) != 0) {
        fprintf(stdout,"Error while create attributes\n");
	}
    if (pthread_create(&child, &attr, &child_thread, NULL) != 0) {
        fprintf(stdout,"Error while creating thread!\n");
	}
    sleep(n);
    pthread_cancel(child);
    pthread_join(child, &result);
    if (result == PTHREAD_CANCELED) {
        fprintf(stdout,"Child thread canceled!\n");
    } else {
		fprintf(stdout, "Pi = %lf\n", *((double*)result));
	}
    return 0;
}
