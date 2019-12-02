#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <math.h>

#define epsilon 0.00001f

typedef struct _thread_arg {
	double a;
    double b;
    double (*func)(double);
    double* res;
} thread_arg;


pthread_mutex_t mutex;

double calc(thread_arg* args, int n){
	double h = (args->b - args->a) / n;
	double x = args->a;
	double res = 0;
	for(int i = 0; i < n; ++i){
		res += h * args->func(x + h / 2);
		x += h;
	}
	return res;
}

void* calc_thread(void* args){
	int n = 10;
	double prev = 0;
	double res = calc((thread_arg *)args, n);
	while(fabs(res - prev) > epsilon){
		prev = res;
		n *= 2;
		res = calc((thread_arg *)args,n);
	}
	pthread_mutex_lock(&mutex);
	*(((thread_arg *)args)->res) += res;
	pthread_mutex_unlock(&mutex);
	return NULL;
}

double f(double x){
	return 4 - (x * x);
}

double integral(int p, int a, int b, double (*func)(double)){
	double res = 0;
	pthread_t threads[p];
	thread_arg args[p];
	pthread_attr_t attr;
	pthread_attr_init(&attr);
	pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);
	double h = ((double)b - a) / p;
	for(int i = 0; i < p; ++i) {
		args[i].a = a + i * h;
		args[i].b = args[i].a + h;
		args[i].func = func;
		args[i].res = &res;
		pthread_create(threads + i, &attr, calc_thread, &args[i]);
	}
	for(int i = 0; i < p; ++i) {
		pthread_join(threads[i], NULL);
	}
	return res;
}

int main(int argc, char** argv){
	if(argc < 2)
		return 0;
	int  p = atoi(argv[1]);
	pthread_mutex_init(&mutex, NULL);
	double res = integral(p, 0, 2, &f);
	pthread_mutex_destroy(&mutex);
	fprintf(stdout, "Res=: %f\n", res);
	return 0;
}
