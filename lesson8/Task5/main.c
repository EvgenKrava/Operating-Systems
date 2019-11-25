#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <time.h>



static pthread_once_t once_var = PTHREAD_ONCE_INIT;
static pthread_key_t thr_key;

void destructor(void* n){
    fprintf(stdout, "Key deleted!\n");
}

void create_key(void){
    fprintf(stdout, "Key created!\n");
    pthread_key_create(&thr_key, &destructor);
}

void* child_thread(void* n){
    char str_out[30];
    pthread_once(&once_var, &create_key);
    pthread_setspecific(thr_key, str_out);
    for(int i = 0; i < rand() % 10 + 1; ++i) {
        sprintf((char*)pthread_getspecific(thr_key), "Thread %d rand number: %d\n", (int)pthread_self(), rand() % 100 + 1);
        fprintf(stdout, "%s", (char*)pthread_getspecific(thr_key));
	sleep(1);
    }
}



void run_thread_pull(int n){
    pthread_t threads[n];
    pthread_attr_t attrib;
    
    pthread_attr_init(&attrib);
    pthread_attr_setdetachstate(&attrib, PTHREAD_CREATE_JOINABLE);
    
    for(int i = 0; i < n; ++i) {
        pthread_create(&threads[i], &attrib, &child_thread, NULL);
	}
    for(int i = 0; i < n; ++i) {
        pthread_join(threads[i], NULL);
	}
    
}

int main(int argc, char** argv){
    if (argc < 2) return 0;
    int n = atoi(argv[1]);
    srand(time(NULL));
    run_thread_pull(n);
    return 0;
}
