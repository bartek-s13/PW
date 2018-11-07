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
    char buf[32];
    int fd[2], n;
    //pid_t a, b;
    
    if (pipe(fd) == -1) 
    {
        perror("pipe creation error");
        exit(1);
    }
    
    if (fork() == 0) 
    {
        close(fd[0]);
        if (write(fd[1], "Hello!\n", 7 ) == -1) {
        perror("child1 write error");
        exit(1);
        }
    close(fd[1]);
    }
    else if(fork() == 0)
    {
        close(fd[1]);
        while ((n = read(fd[0], buf, sizeof(buf))) > 0)
            write(1, buf, n);
        if (n == -1) {
        perror("child2 read error");
        exit(1);
        }
        close(fd[0]);
    }
    else
    {
        close(fd[0]);
        close(fd[1]);
        if (wait(NULL) == -1) 
        {
            perror("wait on child");
            exit(1);
        }
        if (wait(NULL) == -1) 
        {
            perror("wait on child");
            exit(1);
        }  
       
    }
    
}
