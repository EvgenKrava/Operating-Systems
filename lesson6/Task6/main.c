#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char** argv){
    pid_t pid = fork();
    if(pid == 0) {
        fprintf(stdout,"Child process: %d\n", getpid());
        char buff[128];
        sprintf(buff,"ps --pid %d", getpid());
        system(buff);
        return 0;
    } else if(pid > 0) {
        sleep(1);
        fprintf(stdout,"Zombie process: %d\n", pid);
        char buff[128];
        sprintf(buff,"ps --pid %d", pid);
        system(buff);  
        pid_t pid1 = wait(NULL);  
    }
}
