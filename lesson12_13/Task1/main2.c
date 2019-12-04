#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <signal.h>
#include <unistd.h>

int* buffer_ptr;

void my_handler(int signo,siginfo_t *si,void *ucontext){
    printf("Received signal: %d\n",signo);
    if(signo==SIGUSR1){
        buffer_ptr = (int*)shmat(si->si_value.sival_int,NULL,0);
        printf("Child process Received SIGUSR1 signal!\n");
    }else
    if(signo==SIGUSR2){
        printf("Child process Received SIGUSR2 signal!\n");
        int sum=0;
        for(int i=1;i<=buffer_ptr[0];i++)
            sum+=buffer_ptr[i];
        buffer_ptr[0]=sum;
        union sigval val;
        val.sival_ptr = (void*)buffer_ptr;
        sigqueue(getppid(),SIGUSR2,val);
    }else if(signo==SIGTERM){
        printf("Child say Buy!\n");
        exit(0);
    }
}


int main(int argc,char** argv){
    printf("Hello, world!\n");
    struct sigaction act;
    act.sa_sigaction = &my_handler;
    act.sa_flags = SA_SIGINFO;
    printf("Register SIGUSR1... %d\n",sigaction(SIGUSR1,&act,NULL));
    printf("Register SIGUSR2... %d\n",sigaction(SIGUSR2,&act,NULL));
    printf("Register SIGTERM signal... %d\n",sigaction(SIGTERM,&act,NULL));
    while(1)pause();
    return 0;
}
