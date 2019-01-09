#include "init.c"
#define MAX_BUFFER 1024
#define MAX_WORDS 16


int main(int argc, char const *argv[])
{
    key_t key;
    int id, fifo;
    char buf[MAX_BUFFER];
    char *words[MAX_WORDS + 1], *words2[MAX_WORDS + 1];
    // Tworzenie kolejki komunikatów dla klienta
    if ((key = ftok(argv[0], 'T')) == -1) {
        perror("cannot fetch key for client");
        exit(1);
    }

    if ((id = msgget(key, IPC_CREAT | 0666)) == -1) {
        perror("cannot create message queue for client");
        exit(1);
    }
    
    // Otwieranie kolejki serwera
    if ((fifo = open(server_name, O_WRONLY)) == -1) {
        perror("cannot open server fifo");
        exit(1);
    }

    write(fifo, &id, sizeof(int));
    close(fifo);

    struct Message sent, received;
    

    // Czekanie na odpowiedź serwera
    if (msgrcv(id, &received, MSG_SIZE, ANSWER, 0) == -1) {
        perror("cannot receive answer message");
        exit(1);
    }

    if (received.id_nadawcy == SERWER){
      printf("%s\n", received.tresc);
      sent.id_nadawcy = received.id_odbiorcy;
    }
        
 if (fork() == 0){
     if (msgrcv(id, &received, MSG_SIZE, ANSWER, 0) == -1) {
        perror("cannot receive answer message");
        exit(1);
    }     
   split2(received.tresc, words2);
   
   printf("%d: %s", received.id_nadawcy, words2[3]);
   
 } 
  
  while(1){
      printf("> ");
      fgets(buf, MAX_BUFFER, stdin);
      split(buf, words);
      if(strcmp(buf,"\n") == 0)
        {
            continue;
        }
        else
        {           
          if(strncmp(buf, "write -u", 8) == 0){
            sent.mtype = MSG_USR;
            sent.id_odbiorcy = atoi(words[2]);            
          }
          else if(strncmp(buf, "write -r", 8) == 0){
            sent.mtype = MSG_ROOM;
            sent.id_odbiorcy = atoi(words[2]);            
          }  
          else{
              sent.mtype = REQUEST;                
              sent.id_odbiorcy = 0;
            }
        }
      strcpy(sent.tresc, buf);
      
      if (msgsnd(0, &sent, MSG_SIZE, 0) == -1) {
                perror("cannot send answer to client message queue");
                exit(1);
            }
  }
    return 0;
}
