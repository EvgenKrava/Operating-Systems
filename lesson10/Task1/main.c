#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include <getopt.h>

struct _data {
	sem_t sem, sem_w, sem_r;
	int* mass;
	int n;
} data;

void* producer(void* n){
	while(1) {
		sem_wait(&data.sem_w);
		sem_wait(&data.sem);
		int r = rand() % 100;
		data.mass[data.n] = r;
		fprintf(stdout, "Producer %d gen number %d. Size of data is %d\n", (int) pthread_self(), r, ++data.n);
		sem_post(&data.sem);
		sem_post(&data.sem_r);
		sleep(1);
	}
}

void* castomer(void* n){
    while(1){
        sem_wait(&data.sem_r);
        sem_wait(&data.sem);
        fprintf(stdout, "Customer %d read number %d. Size of data is %d\n", (int)pthread_self(), data.mass[data.n], --data.n);
        sem_post(&data.sem);
        sem_post(&data.sem_w);
        sleep(1);
    }
}


void init_data(int n){
    data.mass = (int *)malloc(sizeof(int) * n);
    data.n = 0;
    sem_init(&data.sem, 0, 1);
    sem_init(&data.sem_w, 0, n);
    sem_init(&data.sem_r, 0, 0);
}

void destroy_data(){
    sem_destroy(&data.sem);
    sem_destroy(&data.sem_w);
    sem_destroy(&data.sem_r);
    free(data.mass);
}



void init_pull(int n){
    pthread_t threads[n * 2];
    pthread_attr_t attr;
    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);
	for(int i = 0; i < n * 2; ++i) {
        if(i % 2 == 0) {
			pthread_create(threads + i, &attr, producer, NULL);
		} else { 
			pthread_create(threads + i, &attr, castomer, NULL);
		}
	}
	sleep(10);
	for(int i = 0; i < n * 2; ++i) {
		pthread_cancel(threads[i]);
	}
	for(int i = 0; i < n * 2; ++i) {
		pthread_join(threads[i], NULL);
	}
}



int main(int argc, char** argv){
	int n = 10;
	int n_thr = 10;
	int opt;
	while((opt = getopt(argc, argv, "n:t:")) != -1) {
		if(opt == 'n') {
			n = atoi(optarg);
		}
        if(opt == 't') {
			n_thr = atoi(optarg);
		}
	} 
	init_data(n);
	init_pull(n_thr);
	destroy_data();
	return 0;
}
