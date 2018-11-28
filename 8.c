#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <errno.h>
#include <signal.h>
#include <stdio.h>
#include <sys/wait.h>
#include <string.h>
#include <stdbool.h>
#include <sys/ipc.h>
#include <sys/shm.h>

int main(){

    char *buffer;
    int shmid;
    
    if ((shmid = shmget(0x113, 100, IPC_CREAT | 0660)) == -1) {
        perror("cannot get shared memory segment");
        exit(1);
    }
    
    while(1)
    {
        if(fork() == 0)
        {
            if ((shmid = shmget(0x113, 100, IPC_CREAT | 0660)) == -1) {
            perror("cannot get shared memory segment");
            exit(1);
            }
            if (shmat(shmid, buffer, 0) == (void *) -1) 
            {
                perror("cannot attach shared memory segment");
                exit(1);
            }
            while(1)
                strcpy(buffer, "foobarfoo");
            //exit(1);
        }
        
        if(fork() == 0)
        {
            if ((shmid = shmget(0x113, 100, IPC_CREAT | 0660)) == -1) {
                perror("cannot get shared memory segment");
                exit(1);
            }
            if (shmat(shmid, buffer, 0) == (void *) -1) 
            {
                perror("cannot attach shared memory segment");
                exit(1);
            }
            while(1)
                strcpy(buffer, "Hello world!\n");
            //exit(1);
        }
        //wait(NULL);
        //wait(NULL);
        printf("%s", buffer);
    }
}
