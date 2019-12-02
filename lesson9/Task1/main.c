#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define CNT 10

long x = 0;

void* inc_thread(void *n) {
	for(int i = 0; i < *((int *)n); ++i) {
		x++;
	}
    return NULL;
}

void* dec_thread(void* n) {
	for(int i = 0; i < *((int *)n); i++) {
		x--;
	}
    return NULL;
}

void thread_pull(int n_thr, int n){
	pthread_t threads[n_thr * 2];
	pthread_attr_t thr_attr;
	pthread_attr_init(&thr_attr);
	pthread_attr_setdetachstate(&thr_attr, PTHREAD_CREATE_JOINABLE);
	for(int i = 0; i < n_thr * 2; ++i) {
		if(i % 2 == 0) {
            pthread_create(&threads[i], &thr_attr, inc_thread, &n);
		} else {
			pthread_create(&threads[i], &thr_attr, dec_thread, &n);
		}
    }
	for(int i = 0; i < n_thr * 2; ++i) {
        pthread_join(threads[i], NULL);
	}
}


int main(int argc, char** argv) {
	int n_thr = 10, n = 1;
	char opt;
	while((opt = getopt(argc, argv, "n:t:")) != -1){
		switch(opt){
			case 'n':
				n = atoi(optarg);
				break;
			case 't':
				n_thr = atoi(optarg);
				break;
			default:
				fprintf(stdout, "Error: invalid argument!\n");
			break;
		}
	}
	fprintf(stdout,"N = %d\tT = %d;\n", n,n_thr);
	thread_pull(n_thr, n);
	fprintf(stdout, "X = %ld;\n", x);
	return 0;
}
