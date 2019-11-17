#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>


int main(int argc,char** argv){
    if(argc < 2) {
		return 0;
	}
    
    int n = atoi(argv[1]);
    pid_t pid1 = getpid();
    for(int i = 0; i < n; ++i){
        pid_t pid = fork();
        if(pid == 0){
            fprintf(stdout,"New process pid: %d ppid: %d\n", getpid(), getppid());
            while(1);
            return 0;
        } else if(getpid() != pid1) {
			break;
		}
    }
    if(getpid() == pid1) {
    char buff[128];
    sprintf(buff,"ps --ppid %d;killall a.out", pid1);
    system(buff);
    while(1);
    }
    return 0;
}
