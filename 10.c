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
#include <sys/msg.h>


int n;
struct msgbuf {
long mtype;
char mtext[1024];
};

void koniec() {
    if (msgctl(n, IPC_RMID, NULL) == -1) {
        perror("Uduwanie kolejki");
        exit(1);
    }
    exit(0);
}


int main()
{
    struct msgbuf q;
    q.mtype = 10;
    strcpy(q.mtext, "Hello!\n");
    int a, b;
    if((n = msgget(17, IPC_CREAT | 0600)) == -1){
        perror("tworzenie kolejki");
        exit(1);
    }
    
    if(fork() == 0){
        if((a = msgsnd(n, &q, 1024,0)) == -1){
            perror("Przesyłanie");
            exit(1);
        }        
    }
    
    if(fork() == 0){
        struct msgbuf rec;
        if((b = msgrcv(n, &rec, 1024, 0, 0)) == -1){
            perror("Odbieranie");
            exit(1);
        }  
        printf("%s", rec.mtext);
    }
    
signal(SIGINT, koniec);

    return 0; 
}
