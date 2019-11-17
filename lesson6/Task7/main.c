#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <getopt.h>
#include <wait.h>

pid_t* pids;

int main(int argc, char** argv){
    if(argc < 2) {
		return 0;
	}
	int count;
    double status = 0;
    int n = atoi(argv[1]);
    pids = (pid_t *)malloc(sizeof(pid_t) * n);
    pid_t pid = getpid();
    for(int i = 0; i < n; ++i){
        pids[i] = fork();
        if(pids[i] == 0) {
            execlp("./child", "./child", argv[1], NULL);
            fprintf(stdout,"Error!\n");
        }
    }
    for(int i = 0; i < n; ++i){
        waitpid(pids[i], &count, 0);
		if (WIFEXITED (count)) {
			status += WEXITSTATUS(count);
		} else {
			fprintf(stdout,"Something wrong!\n");
		}
    }
	status /= (double)n;
	printf("status = %lf\n", status);
    free(pids);
    fprintf(stdout,"Pi = %lf\n", status / n * 4);
    return 0;
}



