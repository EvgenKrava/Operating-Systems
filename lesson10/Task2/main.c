#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <getopt.h>

struct _data{
	int* mass;
	int n;
	pthread_cond_t cnd_w;
	pthread_cond_t cnd_r;
	pthread_mutex_t m;
} data;

char running = 1;

void* producer(void* max_n){
	pthread_setcancelstate(PTHREAD_CANCEL_ENABLE, NULL);
	pthread_setcanceltype(PTHREAD_CANCEL_ASYNCHRONOUS, NULL);
	fprintf(stdout, "Producer started\n");
	while(running) {
		pthread_mutex_lock(&data.m);
		while(data.n == *((int *) max_n)){
			pthread_cond_wait(&data.cnd_w, &data.m);
		}
		data.mass[data.n] = rand() % 1000;
		fprintf(stdout, "Thread %lu gen number %d. Size of data is %d\n",(unsigned long)pthread_self(), data.mass[data.n], ++data.n);
		pthread_cond_signal(&data.cnd_r);
		pthread_mutex_unlock(&data.m);
		usleep(100);
	}
	fprintf(stdout, "Producer finished\n");
}

void* consumer(void* max_n){
	pthread_setcancelstate(PTHREAD_CANCEL_ENABLE, NULL);
	pthread_setcanceltype(PTHREAD_CANCEL_ASYNCHRONOUS, NULL);
	fprintf(stdout, "Customer started\n");
	while(running) {
		pthread_mutex_lock(&data.m);
		while(data.n == 0) {
			pthread_cond_wait(&data.cnd_r, &data.m);
		}
		data.mass[data.n] = rand()%1000;
		fprintf(stdout, "Thread %lu read number %d. Size of data is %d\n", (unsigned long)pthread_self(), data.mass[data.n], --data.n);
        pthread_cond_signal(&data.cnd_w);
        pthread_mutex_unlock(&data.m);
        usleep(100);
        
    }   
    fprintf(stdout, "Consumer finished\n");
}

int main(int argc, char** argv){
    int n = 6;
    int n_thr = 10;
    int sleep_time = 1;
    int opt;
    data.n = 0;
    //n-count of data
    //t-count of threads
    //s-count of sleep in Sec
    while((opt = getopt(argc, argv, "n:t:s:")) != -1){
        if (opt == 'n')
            n = atoi(optarg);
        if (opt == 't')
            n_thr = atoi(optarg);
        if (opt == 's')
            sleep_time = atoi(optarg);
    }
    data.mass = (int *)malloc(sizeof(int) * n);
    pthread_t threads[n * 2];
    //pthread_t threads[12];
    pthread_attr_t attr;
    pthread_attr_init(&attr);
    pthread_mutex_init(&data.m, NULL);
    pthread_cond_init(&data.cnd_w, NULL);
    pthread_cond_init(&data.cnd_r, NULL);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);
    for(int i = 0; i < 2 * n; ++i){
        if(i % 2 == 0) {
            pthread_create(&threads[i], &attr, &producer, &n);
        } else {
            pthread_create(&threads[i], &attr, &consumer, NULL);
		}
	}
    sleep(sleep_time * 2);
    running = 0;
    for(int i = 0; i < 2 * n; ++i) {
		if (pthread_join(threads[i], NULL) != 0){
			fprintf(stdout,"FAIL JOIN!\n");
		} else {
			fprintf(stdout,"OK JOIN!\n");
		}
	}
	pthread_mutex_destroy(&data.m);
	pthread_cond_destroy(&data.cnd_w);
	pthread_cond_destroy(&data.cnd_r);
	free(data.mass);
	return 0;
}
