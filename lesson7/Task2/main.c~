#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

struct thread_arg {
	char *name;
	char *str;
	int num;	
};

void *func(void* arg){
	struct thread_arg a = *(struct thread_arg *) arg;
	for(int i = 0; i < a.num; ++i){
		fprintf(stdout, "%s. %s %d\n", a.name, a.str, i);
	}
	return NULL;
}

int main(){
	struct thread_arg arg[4];
	arg[0].name = "One";
	arg[0].str = "str one";
	arg[0].num = 1;
	
	arg[1].name = "Two";
	arg[1].str = "str two";
	arg[1].num = 2;

	arg[2].name = "Three";
	arg[2].str = "str three";
	arg[2].num = 3;

	arg[3].name = "Four";
	arg[3].str = "str four";
	arg[3].num = 4;
	pthread_t thread;
	int result;
	for(int i = 0; i < 4; ++i){
		result = pthread_create(&thread, NULL, &func, &arg[i]);	
	}
	sleep(1);
	return 0;
}
