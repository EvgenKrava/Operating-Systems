#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>

struct arg {
	char *str;
	int count;
};

struct range {
	int count;
	int from;
	int to;
	int exp;
};

void *func1(void *arg){
	printf("Thread 1 start\n");
	struct arg *args = (struct arg *) arg;
	for(int i = 1; i <= args->count; ++i){
		printf("Child 1 Thread. Message: %s. Iteration: %d;\n", args->str, i);
		sleep(1);
	}
	printf("Thread 2 finish\n");
	return NULL;
}

void *func2(void *arg) {
	printf("Thread 2 start\n");
	struct range *args = (struct range *) arg;
	for(int i = 0; i < args->count; ++i) {
		int a = rand() % (args->to + 1 - args->from) + args->from;
		printf("Child 2 Thread. Random number: %d Iteration: %d;\n", a, i + 1);
		sleep(1);
		if(a == args->exp){
			printf("Random number was equals expectation number. Interrapt thread!\n");
			break;
		}
	}
	printf("Thread 2 finish\n");
	return NULL;
}

int main(){
	printf("Program start\n");
	srand(time(NULL));

	struct arg arg1;
	arg1.str = "message";
	arg1.count = 5;

	struct range r;
	r.from = 1;
	r.to = 10;
	r.exp = 7;
	r.count = 5;	
	pthread_t thread1;
	pthread_t thread2;
	pthread_create(&thread1, NULL, &func1, &arg1);
	pthread_create(&thread2, NULL, &func2, &r);
	pthread_join(thread1, NULL);
	pthread_join(thread1, NULL);
	printf("Program finish\n");
	return 0;
}
