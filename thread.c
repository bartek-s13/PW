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

int main(){
    //int tab[10000000];
    pthread_t id;
    int wynik;
    int a = 5;
    void *res;
    if (pthread_create(&id, NULL, f1, &a)!= 0) {
        perror("creating thread");
        exit(-1);
    }   
    sleep(2);
    pthread_join(id, &res);

    printf("Result: %d", *((int*)res));
    return 0;
}
