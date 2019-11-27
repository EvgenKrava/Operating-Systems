#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <math.h>

int is_prime(int a) {
	for(int i = 2; i < sqrt(a); ++i) {
		if(a % i == 0) {
			return 0;
		}
	}
	return 1;
}

long int fact(int n){
	if (n <= 1) {
		return 1;
	}
	return n * fact(n - 1);
}

void *func1(void *arg){
	printf("Katalan's numbers start\n");
	int n = *(int *)arg;
	int *kat = malloc(sizeof(int) * n);
	for (int i = 0; i < n; ++i){
		kat[i] = fact(2 * i) / (fact(i + 1) * fact(i));
	}
	printf("Katalan's numbers finish\n");
	pthread_exit(kat);
	return NULL;
}

void *func2(void *arg) {
	printf("Simple numbers start\n");
	int n = *(int *) arg;
	int *sim = malloc(sizeof(int) * n);
	for (int i = 2, k = 0; k < n; ++i) {
		if (is_prime(i)) {
			sim[k] = i;
			k++;	
		}
	}
	printf("Simple numbers finish\n");
	pthread_exit(sim);
	return NULL;
}

int main(int argc, char **argv){
	printf("Program start\n");
	int n = 10;
	if (argc > 1) {
		n = atoi(argv[1]);
	}
	pthread_t thread1;
	pthread_t thread2;
	int *kat;
	int *sim;
	pthread_create(&thread1, NULL, &func1, &n);
	pthread_create(&thread2, NULL, &func2, &n);
	pthread_join(thread1, (void *) &kat);
	pthread_join(thread2, (void *) &sim);
	
	printf("Katalan's numbers:\n");
	for(int i = 0; i < n; ++i) {
		printf("%d ", kat[i]);
	}
	printf("\n");

	printf("Simple numbers:\n");
	for(int i = 0; i < n; ++i) {
		printf("%d ", sim[i]);
	}
	printf("\n");

	free(kat);
	free(sim);
	printf("Program finish\n");
	return 0;
}
