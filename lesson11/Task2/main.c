#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>


#define tim_cnt 1

pid_t pid;

void my_handler(int signo){
    if(signo==SIGUSR1){
        sleep(tim_cnt);
        if(pid==0){
            printf("Child process message!\n");
            kill(getppid(),SIGUSR1);
        }else{
            printf("Parent process message!\n");
            kill(pid,SIGUSR1); 
        }
    }
}

int main(int argc,char**  argv){
    signal(SIGUSR1,&my_handler);
    pid = fork();
    if(pid==0){
        printf("Child process %d\n",getpid());
        while(1){
            pause();
        }
    }else{
        printf("Parent process %d\n",getpid());
        kill(pid,SIGUSR1);
        while(1){
            pause();
        }        
    }
    return 0;
}
