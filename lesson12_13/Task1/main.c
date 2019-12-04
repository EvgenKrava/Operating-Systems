#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <signal.h>
#include <unistd.h>
#include <wait.h>


int* buffer;


void my_handler(int signo,siginfo_t *si,void *ucontext){
    if(signo==SIGUSR2){
        printf("Parent process Received SIGUSR2 signal!\n");
        printf("Result is %d\n",buffer[0]);
    }else if(signo==SIGTERM){
        shmdt(buffer);
        printf("Parent say Buy!\n");
    }
}

void main_thread(pid_t pid,int dsk){
        int n;
        struct sigaction act;
        act.sa_sigaction = &my_handler;
        act.sa_flags=SA_SIGINFO;
        printf("Parent thread register SIGUSR2 signal... %d\n",sigaction(SIGUSR2,&act,NULL));
        printf("Parent thread register SIGTERM signal... %d\n",sigaction(SIGTERM,&act,NULL));
        union sigval val;
        val.sival_int=dsk;
        //kill(pid,SIGUSR1);
        if(sigqueue(pid,SIGUSR1,val))
            printf("Error in initialization of child process!\n");
        while(1){
            sleep(1);
            printf("Enter n:\n#: ");
            scanf("%d",&n);
            if(n==-1){
                kill(pid,SIGTERM);
                raise(SIGTERM);
                return;
            }
            buffer[0]=n;
            printf("Enter n numbers:\n#: ");
            for(int i=1;i<=n;i++)
                scanf("%d",&buffer[i]); 
            printf("Calculating...\n");
            kill(pid,SIGUSR2);
            pause();
        }
}

int main(int argc,char** argv){
    int buff_size = 512;
    if(argc>1)buff_size=atoi(argv[1]);
   int shm_dsc = shmget(IPC_PRIVATE,buff_size,IPC_CREAT | IPC_EXCL | 0600);
    if(shm_dsc == -1){
        printf("Error: can't create shared memory\n");
        return 0;
    }
    buffer =(int*) shmat(shm_dsc,NULL,0);
    pid_t pid = fork();
    if(pid==0){
        printf("Starting child process...!\n");
        char* args[]={"./child",NULL};
        execv("./child",args);
        printf("Error!\n");
        return 0;
    }else if(pid>0){
        //pause();
        sleep(1);
        main_thread(pid,shm_dsc);
    }
    wait(NULL);
    return 0;
}
