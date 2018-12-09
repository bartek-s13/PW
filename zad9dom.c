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
#include <signal.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>

static struct sembuf buf;

void podnies (int semid, int semnum) {
    buf.sem_num = semnum;
    buf.sem_op = 1;
    buf.sem_flg = 0;
    if (semop(semid, &buf, 1) == -1) {
        perror("podnoszenie semafora");
        exit(1);
    }
}

void opusc(int semid, int semnum) {
    buf.sem_num = semnum;
    buf.sem_op = -1;
    buf.sem_flg = 0;
    if (semop(semid, &buf, 1) == -1) {
        perror("opuszczenie semafora");
        exit(1);
    }
}

void filozof(int nr, int a){
    while(1){
        int c,d; //widelce
        c = nr;
        if(nr == 1)
          d = 5;
        else
          d = nr - 1;
            podnies(a, c);
            printf("%d bierze widelec %d", nr, c);
            podnies(a, d);
            printf("%d bierze widelec %d", nr, d);
            printf("%d je", nr);
            sleep(2);
            opusc(a, c);
            printf("%d odkłada widelec %d", nr, c);
            opusc(a, d);
            printf("%d odkłada widelec %d", nr, d);
}
    
}


int main()
{
    int a = semget(0x777, 5, IPC_CREAT| 0660);
    for(int j = 0; j<5; j++)
        semctl(a, j, SETVAL, 1);
for(int i = 1; i<=5; i++){
     if(fork() == 0){
        filozof(i, a);
    }
    
}    
   
return 0;    
    
    

    
}
