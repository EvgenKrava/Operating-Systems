#include <stdio.h>
#include <signal.h>
#include <unistd.h>

int k = 1;

void print(int signo){
	printf("%s\n", sys_siglist[signo]);
	k = 0;
}

int main(int argc, char **argv){	
	signal(SIGALRM, print);
	printf("start\n");
	alarm(atoi(argv[1]));
	int i = 0;
	while(k) {
		printf("%d\n", ++i);
		sleep(1);
	}
	printf("finish\n");
	return 0;
} 
