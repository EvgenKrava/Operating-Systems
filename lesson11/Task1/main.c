#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <signal.h>
#include <unistd.h>

//SIGINIT захват
//SIGTERM захват
//SIGPROF по-умолчанию
//SIGHUP  игнор

void new_sigint(int n){
    fprintf(stdout,"SIGINIT received!\n");
    return;
}

void new_sigterm(int n){
    fprintf(stdout,"SIGTERM received!\n");
}

int main(int argc,char** argv){
    fprintf(stdout,"Process pid is %d\n",getpid());
    if(signal(SIGINT,&new_sigint)==SIG_ERR)
        fprintf(stdout,"Error while register SIGINT handler!\n");
    else
        fprintf(stdout,"SIGINT handler successful registred!\n");
    if(signal(SIGTERM,&new_sigterm)==SIG_ERR)
        fprintf(stdout,"Error while register SIGTERM handler!\n");
    else
        fprintf(stdout,"SIGTERM handler successful registred!\n");
    if(signal(SIGPROF,SIG_DFL)==SIG_ERR)
        fprintf(stdout,"Error while register SIGPROF handler!\n");
    else
        fprintf(stdout,"SIGPROF handler successful registred!\n");
    if(signal(SIGHUP,SIG_IGN)==SIG_ERR)
        fprintf(stdout,"Error while register SIGHUP handler!\n");
    else
        fprintf(stdout,"SIGHUP handler successful registred!\n");
    while(1)pause();
    return 0;
}
