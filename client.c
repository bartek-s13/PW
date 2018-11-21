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

int main(){
    char sname[] = "serfifo", cname[] = "clfifo";
    int fds, fdc, n, i;
    char buf[1024], messg[1024];
    bool on = true;
    
    if(mkfifo(cname, S_IRUSR | S_IWUSR) == -1)
    {
        perror("client fifo create error");
        exit(1);
    } 
    
    if((fds = open(sname, O_WRONLY)) == -1)
    {
                perror("server fifo open error");
                exit(1);
    } 
    
     if((fdc = open(cname, O_WRONLY)) == -1)
    {
                perror("server fifo open error");
                exit(1);
    } 
    
    while(on)
    {
        printf("> ");
        if(n = read(0, buf, 1024)
        {
            i = 0;
            while(cname[i] != '\0')
            {
                messg[i] = cname[i];
                i++;
            }
            messg[i] = '@';
        
        }
        
    }
}
