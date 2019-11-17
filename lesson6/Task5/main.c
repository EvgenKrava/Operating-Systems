#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>

int my_system(const char* cmd){
    pid_t pid = fork();
    int status;
    if(pid == 0){
        execlp("/bin/bash", "/bin/bash", "-c", cmd, NULL);
    }else if(pid > 0)
        return waitpid(pid, &status, 0);
}

int main(int argc, char** argv){
    my_system("ls -l");
    return 0;
}
