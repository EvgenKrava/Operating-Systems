#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <signal.h>
#include <unistd.h>

#define SEM_KEY 2017
#define SHM_KEY "/home/cranch/putty.log"

union semnum{
    int val;
    struct semid_ds *buf;
    unsigned short * array;
}sem_arg;




int main(int argc,char** argv){
    key_t token =ftok(SHM_KEY,1);
    int shm_handler = shmget(token,128,IPC_CREAT | IPC_EXCL | 0600);
    int sem_handler = semget(SEM_KEY,1, IPC_CREAT | IPC_EXCL | 0600);
    unsigned short sem_vals[1];
    struct semid_ds ds;
    struct sembuf sb[1];
    if(shm_handler == -1){
        printf("Parent: Can't create shared memory!\n");
        return 0;
    }
    if(sem_handler == -1){
        printf("Parent: can't create semaphore!\n");
        return 0;
    }
    int* buffer =shmat(shm_handler,NULL,0);
    if(buffer == (int*) -1){
        printf("Parent: Can't get memory address!\n");
    }
    
    sem_vals[0] = 1;
    sem_arg.array=sem_vals;
    if(semctl(sem_handler,0,SETALL,sem_arg)==-1){
        printf("Parent: semctl() error!\n");
        return 0;
    }
    
    //close semaphore
    sb[0].sem_flg =0;
    sb[0].sem_num=0;
    sb[0].sem_op=-1;
    semop(sem_handler,sb,1);
    
    pid_t pid  = fork();
    if(pid==0){
        char* args[]={"./child","./child",NULL};
        execv("./child",args);
        printf("Error: can't create process!\n");
    }else{
        while(1){
            int n;
            printf("Enter n\n");
            scanf("%d",&n);
            buffer[0]=n;
            printf("Enter n numbers!\n");
            for(int i=1;i<=n;i++){
                scanf("%d",&buffer[i]);
            }
    sb[0].sem_flg =0;
    sb[0].sem_num=0;
    sb[0].sem_op=1;
    semop(sem_handler,sb,1);
            usleep(100);
    sb[0].sem_flg =0;
    sb[0].sem_num=0;
    sb[0].sem_op=-1;
    semop(sem_handler,sb,1);
            printf("Answer is %d\n",buffer[0]);
        }
        
    }
    
    return 0;
}
