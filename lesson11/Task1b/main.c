#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

//SIGINT захват
//SIGTERM захват
//SIGPROF по-умолчанию
//SIGHUP игнор


void new_handler(int signo,siginfo_t *si,void* ucontext){
    if (signo == SIGINT)
        fprintf(stdout,"Received SIGINT signal!\n");
    else if(signo == SIGTERM)
        fprintf(stdout, "Received SIGTERM signal!\n");
    else
        fprintf(stdout, "received unknown signal!\n");
}

int main(int argc, char** argv){
    struct sigaction new_sig;
    new_sig.sa_sigaction = &new_handler;
    new_sig.sa_flags = SA_SIGINFO;
    printf("Thread pid is %d\n", getpid());
    if(sigaction(SIGINT, &new_sig, NULL) == 1)
        fprintf(stdout,"Error while register SIGINT handler!\n");
    else
        fprintf(stdout, "SIGINT handler successful registred!\n");;
    if(sigaction(SIGTERM, &new_sig, NULL) == 1)
        fprintf(stdout, "Error while register SIGTERM handler!\n");
    else
        fprintf(stdout, "SIGTERM handler successful registred!\n");
    new_sig.sa_flags = 0;
    new_sig.sa_handler = SIG_IGN;
    if(sigaction(SIGHUP, &new_sig, NULL)==1)
        fprintf(stdout, "Error while register SIGHUP handler!\n");
    else
        fprintf(stdout, "SIGHUP handler successful registred!\n");
    new_sig.sa_handler = SIG_DFL;
    if(sigaction(SIGPROF,&new_sig,NULL)==1)
        fprintf(stdout,"Error while register SIGPROF handler!\n");
    else
        fprintf(stdout,"SIGPROF handler successful registred!\n");
    while(1){
		pause();
	}
    return 0;
}
