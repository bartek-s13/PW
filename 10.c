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

#define M_DANE 997
#define M_END 998
#define M_WYNIK 999

int n;
struct msgbuf {
long mtype;
int mnumber;
};

int main()
{
    if((n = msgget(17, IPC_CREAT | 0600)) == -1){
        perror("tworzenie kolejki");
        exit(1);
    }
    int a, b;
  
    if(fork() == 0){   
        struct msgbuf q;
        while(1){
        do{
            printf("Podaj liczbę: \n");        
            scanf("%d", &q.mnumber);
            if(q.mnumber != 0)
                q.mtype = M_DANE;
            else
                q.mtype = M_END;
            if((a = msgsnd(n, &q, sizeof(int),0)) == -1){
                perror("Przesyłanie");
                exit(1);
            }         
        }while(q.mnumber != 0);
        q.mnumber++;
        if((a = msgrcv(n, &q, sizeof(int), 999, 0)) == -1){
            perror("Odbieranie");
            exit(1);
        }  
        printf("Otrzymany wynik to: %d \n", q.mnumber);          
        }
    }    
    
    if(fork() == 0){
        struct msgbuf rec;
        int sum = 0;
        while(1){
            if((b = msgrcv(n, &rec, sizeof(int), 0, 0)) == -1){
                perror("Odbieranie");
                exit(1);
            }    
            if(rec.mtype == M_DANE)
                sum += rec.mnumber;
            else if(rec.mtype == M_END){
                rec.mtype = M_WYNIK;
                rec.mnumber = sum;
            if((a = msgsnd(n, &rec, sizeof(int),0)) == -1){
                perror("Przesyłanie");
                exit(1);
            }    
            sum = 0;          
            }       
        }
    }
    

  wait(NULL);
  wait(NULL);
  return 0; 
}
