#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/sem.h>
#include <sys/mman.h>
#include <fcntl.h>

#define KEY 2017
#define FILENAME "buffer"


void A_semaphore(int id,int cnt,struct sembuf* sb){
    sb[0].sem_num=0;
    sb[0].sem_flg=0;
    sb[0].sem_op=cnt;
    semop(id,sb,1);
}

void D_semaphore(int id,int cnt,struct sembuf* sb){
    sb[0].sem_num=0;
    sb[0].sem_flg=0;
    sb[0].sem_op=-cnt;
    semop(id,sb,1);
}


int main(int argc,char** argv){
    struct sembuf sb[1];
    int sem_id = semget(KEY,1, 0600 | IPC_CREAT | IPC_EXCL);
    if(sem_id==-1){
        fprintf(stderr,"Parent error! Can't open semaphore!\n");
        return 1;
    }
    int file_desc = open(FILENAME, O_RDWR | O_CREAT | O_TRUNC, 0600);
    if(file_de-1){
        fprintf(stderr,"Parent error! Can't open file!\n");
        return 1;
    }
    int* buffer =(int*) mmap(NULL,127, PROT_WRITE | PROT_READ, MEM_SHARED,file_desc,0);
    if((char*)buffer == MAP_FAILED){
        fprintf(stderr,"Parent error! Can't map file!\n");
    }
    close(file_desc);
    pid_t pid = fork();
    if(pid==0){
        char* args[]={"./child","./child",NULL};
        execv("./child",args);
        fprintf(stderr,"Parent error! Can't execute child process!\n");
        return 1;
    }else{
        while(1){
        D_semaphore(sem_id,1);
        int n,sum;
        n=buffer[0];
        sum=0;
        for(int i=1;i<=n;i++)
            sum+=buffer[i];
        buffer[0]=sum;
        A_semaphore(sem_id,1);
        uslepp(100);
        }
    }
    
    return 0;
}
