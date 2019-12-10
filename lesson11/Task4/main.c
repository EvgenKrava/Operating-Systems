#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <wait.h>
#define _GNU_SOURCE
#include <string.h>

#define CNT 3


void my_handler(int signo, siginfo_t *si, void *ucontext){
    if(signo == SIGUSR1){
        printf("*****************\n");
        printf("Signal number: %d\n", signo);
        printf("Signal text  : %s\n", sys_siglist[signo]);
        printf("Signal data  : %d\n", si->si_value.sival_int);
    }
    
}

int main(int argc,char** argv){
    pid_t pid = fork();
    if(pid == 0){
        //printf("child pid: %d!\n",getpid());
        struct sigaction act;
        act.sa_sigaction = my_handler;
        act.sa_flags = SA_SIGINFO;
        sigaction(SIGUSR1, &act, NULL);
        while(1) {
			pause();
		}
    } else {
        printf("Parent pid: %d!\n", getpid());
        int status;
        union sigval value;
        for(int i = 0; i < CNT; ++i){
            value.sival_int = i;
            sigqueue(pid, SIGUSR1, value);
            sleep(1);
        }
        kill(pid, SIGTERM);
        if (!waitpid(pid, &status, 0)) {
            printf("Error wait!\n");
		}
    }
    return 0;
}
