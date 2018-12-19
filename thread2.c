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
#include <pthread.h>

#define size 1000000;

void *f1(void *arg1){
    int *q = (int*) arg1;
   // int result = 1;
    //int a = *q;
    //printf("%d\n", a);
    /*
    while(a != 0){
        result *= a;
        a--;
    }
    */
    //*q = result;
    return q;
}
int tab[size];

int main(){

     pthread_t id[10];
    int wynik;
    void *a[10];
    //void *res;
    int x = size/10;
    for(int i = 0; i < size; i++)
        tab[i] = 1;

    for(int i = 0; i < 10; i++){
        if (pthread_create(&(id[i]), NULL, f1, &x)!= 0) {
            perror("creating thread");
            exit(-1);
        } 
        x += (size/10);
    }

    for(int i = 0; i < 10; i++){
        pthread_join(id, &res);
        x += (size/10);
    }
   

    sleep(2);
    pthread_join(id, &res);

    printf("Result: %d", wynik);
    return 0;
}