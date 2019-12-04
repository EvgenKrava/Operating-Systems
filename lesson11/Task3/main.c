#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <signal.h>


char* msg;

void my_handler(int signo){
    printf("%s\n",msg);
}


int main(int argc,char** argv){
    if(argc<3)return 0;
    msg = argv[2];
    int n = atoi(argv[1]);
    alarm(n);
    pause();
    return 0;
}
