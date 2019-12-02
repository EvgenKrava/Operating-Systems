#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <string.h>


struct _data {
	int* arr;
	int n;
	pthread_rwlock_t lock;
} data;


void destructor(void){
	if (data.arr != 0) {
		free(data.arr);
	}
	pthread_rwlock_destroy(&data.lock);
}

void* read_thread(void* n){
	int pos = 0;
	while(1) {
		usleep(500);
		pos = rand() % data.n;
		while(pthread_rwlock_rdlock(&data.lock) != 0);
		fprintf(stdout, "thread %du read value %d from arr[%d] \n", (int)pthread_self(), data.arr[pos], pos);
        pthread_rwlock_unlock(&data.lock);
    }
}

void* write_thread(void* n){
	int pos = 0;
	while(1) {
		usleep(400);
		pos = rand() % data.n;
		data.arr[pos] = rand() % 1000;
		while(pthread_rwlock_wrlock(&data.lock) != 0);
		fprintf(stdout,"thread %du write value %d from arr[%d] \n", (int)pthread_self(), data.arr[pos], pos);
		pthread_rwlock_unlock(&data.lock);
	}
}

void* print_thread(void* n){
	while(1){
		usleep(100000);
		while(pthread_rwlock_rdlock(&data.lock)!=0);
		for(int i = 0; i < data.n; ++i)
			fprintf(stdout, "%d ", data.arr[i]);
		fprintf(stdout, "\n");
		pthread_rwlock_unlock(&data.lock);
    }
}

void run_threads(int n){
	pthread_t read_threads[n*2];
	pthread_t write_threads[n];
	pthread_t det_thrd;
	pthread_attr_t jattr,dattr;
	pthread_attr_init(&jattr);
	pthread_attr_init(&dattr);
	pthread_attr_setdetachstate(&jattr,PTHREAD_CREATE_JOINABLE);
	pthread_attr_setdetachstate(&dattr,PTHREAD_CREATE_DETACHED);
	for(int i = 0; i < n; ++i) {
		pthread_create(&write_threads[i],&jattr,&write_thread,&n);
	}
    for(int i = 0; i < n * 2; ++i) {
        pthread_create(&read_threads[i], &jattr,&read_thread, &n);
	}
    pthread_create(&det_thrd, &dattr, &print_thread, &n);
}


int main(int argc, char** argv){
	atexit(destructor);
	int n = 10;
	char opt;
	while((opt = getopt(argc, argv, "n:")) != -1){
		if (opt == 'n'){
			n=atoi(optarg);
		}
    }
    data.n = n;
    data.arr = (int *)malloc(sizeof(int) * n);
    memset(data.arr, 0, sizeof(int) * n);
    pthread_rwlock_init(&data.lock, NULL);
    run_threads(n);
    while(1);
    return 0;
}
