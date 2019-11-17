#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <getopt.h>
#include <string.h>


void mgetpid(){
    pid_t t=getpid();
    fprintf(stdout,"Pid: %d\n",t);
}
void mgetppid(char* buf){
    pid_t t=getppid();
    fprintf(stdout,"Ppid: %d\n",t);
}
void mgetpgrp(){
    pid_t t=getpgrp();
    fprintf(stdout,"PGrp: %d\n",t);    
}
void mgetuid(){
    pid_t t=getuid();
    fprintf(stdout,"Uid: %d\n",t); 
}
void mgeteuid(){
    pid_t t=geteuid();
    fprintf(stdout,"Euid: %d\n",t); 
}
void mgetgid(){
    pid_t t=getgid();
    fprintf(stdout,"Gid: %d\n",t); 
}
void mgetegid(){
    pid_t t=getegid();
    fprintf(stdout,"Egid: %d\n",t); 
}

void print_help(){
    fprintf(stdout,"Usage: pi [--pid] [--ppid] [--grp] [--uid] [--euid] [--gid] [--egid] [--all]\n");
}

int main(int argc,char** argv){
    const struct option long_opt[]={
        {"pid",0,0,'P'},
        {"ppid",0,0,'p'},
        {"grp",0,0,'g'},
        {"uid",0,0,'u'},
        {"euid",0,0,'U'},
        {"gid",0,0,'i'},
        {"egid",0,0,'I'},
        {"all",0,0,'a'}
    };
    if(argc<2){
        print_help();
        return 0;
    }
	int arr[7] = {0, 0, 0, 0, 0, 0, 0};
	void (*f[7])() = {mgetpid, mgetppid, mgetpgrp, mgetuid, mgeteuid, mgetgid, mgetegid};
    int cmd;
    while((cmd=getopt_long(argc,argv,"PpguUiIa",long_opt,NULL))!=-1){
        switch(cmd){
            case 'P':
                arr[0] = 1;
                break;
            case 'p':
                arr[1] = 1;
                break;
            case 'g':
                arr[2] = 1;
                break;
            case 'u':
                arr[3] = 1;
                break;
            case 'U':
                arr[4] = 1;
                break;
            case 'i':
                arr[5] = 1;
                break;
            case 'I':
                arr[6] = 1;
                break;
            case 'a':
				for(int i = 0; i < 7 ; ++i){
					arr[i] = 1;
				}
				break;
			case '?':
				print_help();
			
        }
    }

    for(int i = 0; i < 7; i++){
        if(arr[i] == 1){
            f[i]();
        }
    }
    return 0;
}



 
