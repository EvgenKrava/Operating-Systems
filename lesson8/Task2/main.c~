#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>


void* child_thread(void* param){
    pthread_setcancelstate(PTHREAD_CANCEL_ENABLE, NULL);
    pthread_setcanceltype(PTHREAD_CANCEL_ASYNCHRONOUS, NULL);
    fprintf(stdout,"Child thread started!\n");
    int cnt = 0;
    while(1) {
        fprintf(stdout,"Child thread Iterate %d\n", cnt);
        cnt++;
        sleep(1);
    }
}


int main(int argc, char** argv) {
    if (argc < 2)
		return 0;
    int n = atoi(argv[1]);
    void* retval;
    pthread_t child;
    pthread_attr_t attr;
    if (pthread_attr_init(&attr) != 0) {
        fprintf(stdout,"Can't initialize thread attributes!\n");
        return 0;
    }
    if (pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE) != 0) {
        fprintf(stdout,"Can't set joinable attributes!\n");
        return 0;   
    }
    
    if (pthread_create(&child, &attr, &child_thread, NULL) != 0) {
        fprintf(stdout,"Can't create child thread!\n");
        return 0;
    }
    sleep(n);
    
    if (pthread_cancel(child) != 0) {
        fprintf(stdout,"Error in canceling child thread!\n");
    }
    if (pthread_join(child,&retval) != 0) {
        fprintf(stdout,"Error while closing child chread\n");
      
    }
    if (retval == PTHREAD_CANCELED) {
        fprintf(stdout,"Child thread canceled!\n");
	} else { 
		fprintf(stdout,"Child thread not canceled!\n");
	}
    return 0;
}
