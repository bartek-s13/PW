#include "init.c"
#define MAX_BUFFER 1024
#define MAX_WORDS 16

int main(int argc, char const *argv[])
{
    key_t key;
    int id, fifo, i;
    char buf[MAX_BUFFER];
    char *words[MAX_WORDS + 1];
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

    struct Message msg;
    

    // Czekanie na odpowiedź serwera
    if (msgrcv(id, &msg, MSG_SIZE, ANSWER, 0) == -1) {
        perror("cannot receive answer message");
        exit(1);
    }

    if (msg.id_nadawcy == SERWER)
        printf("%s\n", msg.tresc);
  
  
  while(1){
      printf("> ");
      fgets(buf, MAX, stdin);
      msg.id_nadawcy = id;
      n = split(buf, words);
      if(strcmp(buf,"\n") == 0)
        {
            continue;
        }
        else
        {
            if ((strncmp(buf, "createRoom", 10) == 0) || (strncmp(m_usr.tresc, "finger", 6) == 0)){
              msg.mtype = REQUEST;                
              msg.id_odbiorcy = 0;
            }
          else if(strncmp(buf, "write -u", 8) == 0)){
            msg.mtype = MSG_USR;
            msg.id_odbiorcy = words[1];            
          }
          else if(strncmp(buf, "write -r", 8) == 0)){
            msg.mtype = MSG_ROOM;
            msg.id_odbiorcy = words[1];            
          }   
        }
    
  }
  
