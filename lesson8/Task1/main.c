#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <string.h>
#include <time.h>

int *global_data;

void *thread_function(void *n) {
    fprintf(stdout, "Thread %d started\n", *((int *) n));
    sleep(*((int *) n));
	int sec = rand() % 10 + 1;
    global_data[*((int *) n)] = sec;
	sleep(sec);
    fprintf(stdout, "Thread %d finished\n", *((int *) n));
    return NULL;
}

void *daemon_function(void *n) {
    int cnt;
    while (1) {
        cnt = 0;
        for (int i = 0; i < *((int *) n); i++) {
            if (global_data[i] == 0)cnt++;
            fprintf(stdout, "%d ", global_data[i]);
        }
        fprintf(stdout, "\n");
        if (!cnt)break;
        sleep(1);
    }
    fprintf(stdout, "Daemon finished\n");
    return NULL;
}

void build_thread_pull(pthread_t *pull, int n) {
    int args[n];
    for (int i = 0; i < n; i++) {
        args[i] = i;
        if (pthread_create(&pull[i], NULL, &thread_function, &args[i]) != 0)
            fprintf(stdout, "Can't create thread #%d\n", i);
    }
    for (int i = 0; i < n; i++)
        if (pthread_join(pull[i], NULL) != 0)
            fprintf(stdout, "Thread #%d finished with error\n", i);
}

void run_daemon(int *n) {
    pthread_t handler;
    pthread_attr_t dattr;
    if (pthread_attr_init(&dattr) != 0) {
        fprintf(stdout, "Can't initialize attributes for daemon!\n");
        return;
    }
    if (pthread_attr_setdetachstate(&dattr, PTHREAD_CREATE_DETACHED) != 0) {
        fprintf(stdout, "Can't initialize detach for daemon!\n");
        return;
    }
    if (pthread_create(&handler, &dattr, &daemon_function, n) != 0) {
        fprintf(stdout, "Can't create daemon!\n");
        return;
    }
    pthread_attr_destroy(&dattr);
}

int main(int argc, char **argv) {
    if (argc < 2) {
        return 0;
    }
    srand(time(NULL));
    int n = atoi(argv[1]);
    pthread_t *threads = (pthread_t *) malloc(sizeof(pthread_t) * n);
    global_data = (int *) malloc(sizeof(int) * n);
    memset(global_data, 0, sizeof(int) * n);
    run_daemon(&n);
    build_thread_pull(threads, n);
    fprintf(stdout, "Main thread finished!\n");
    pthread_exit(0);
}
