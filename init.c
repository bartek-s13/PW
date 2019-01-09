#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <signal.h>
#include <errno.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>

#define MAX_TRESC 1024
#define SERWER 0

#define REQUEST 1  // żądanie do serwera
#define MSG_USR 2  // wiadomość do użytkownika
#define MSG_ROOM 3 // wiadomość do pokoju
#define ANSWER 4   // odpowiedź serwera

char server_name[] = "server_fifo";

struct Message {
    long mtype;             // typ wiadomości
    int id_nadawcy;         // 0 - serwer, [1, ...) - klient
    int id_odbiorcy;        // 0 - serwer, [1, ...) - id klienta/pokoju
    int data_wyslania;      // zakodowana data w określonym systemie
    char tresc[MAX_TRESC];  // wiadomosc lub komenda dla serwera
} toSize;

const int MSG_SIZE = sizeof(toSize) - sizeof(long);

void split(char str[], char* str2[]) {
    str2[0] = str;
    int i=1;  
    while(*str != '\0') {
        if(*str == ' ') {
            *str = '\0';
            str2[i] = ++str;
            ++i;            
        }
        else
            ++str;
    }
    *(--str) = '\0';
    str2[i] = NULL;
}

void split2(char str[], char* str2[]) {
    str2[0] = str;
    int i=1;
    int j = 3;
    while(*str != '\0') {
        if((*str == ' ') && j !=0 ) {
            *str = '\0';
            str2[i] = ++str;
            ++i;  
            j--;
        }
        else
            ++str;
    }
    *(--str) = '\0';
    str2[i] = NULL;
}
