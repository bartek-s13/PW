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
int a;

void koniecimprezy() {
    if (semctl(a, 0, IPC_RMID, NULL) == -1) {
        perror("cannot remove semaphore");
        exit(1);
    }
    exit(0);
}

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

void filozof(int nr){    
        int l,r; //widelce
        r = nr;
        if(nr == 0)
          l = 4;
        else
          l = nr - 1;
	while(1){
            opusc(a, r);
            printf("%d bierze widelec prawy(%d)\n", nr + 1, r + 1);
            opusc(a, l);
            printf("%d bierze widelec lewy (%d)\n", nr + 1, l + 1);
            printf("%d je\n", nr + 1);
            sleep(2);            
            podnies(a, l);
            printf("%d odkłada widelec lewy(%d)\n", nr + 1, l + 1);
            podnies(a, r);
            printf("%d odkłada widelec prawy (%d)\n", nr + 1, r + 1);
	}
   
}


int main()
{
    if ((a = semget(0x123, 5, IPC_CREAT | 0777)) == -1){
        perror("Cannot get semaphore");
        exit(1);
    }
    for(int j = 0; j<5; j++)
        semctl(a, j, SETVAL, 1);
    for(int i = 0; i<5; i++){ 
	if(fork() == 0){
	filozof(i);
	}
    }   
        
    
signal(SIGINT, koniecimprezy);
    while(1);
   
    return 0; 
}
