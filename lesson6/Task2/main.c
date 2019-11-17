#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/types.h>
#include <unistd.h>


int main(int argc,char** argv){
    time_t now = time(NULL); //seconds from 01.01.1979 to now
    pid_t pid = fork();
    int tmp = 0;
    while((time(NULL) - now) < 2){
		tmp++;
	}
    if(pid == 0) {
		fprintf(stdout,"Child process tmp:  %d\n", tmp);
	} else if(pid > 0) {
		fprintf(stdout,"Parent process tmp: %d\n", tmp);
	} else {
		fprintf(stdout,"Error: can`t create process!\n");
	}
}
