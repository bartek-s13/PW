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
    char name1[] = "myfifo1", name2[] = "myfifo2";
    int fd,fd1;
    unlink(name1);
    unlink(name2);
    if (mkfifo(name1, S_IRUSR | S_IWUSR) == -1) //jak plik, czyli dawa razy nie możemy utworzyć dwa razy
    {
        perror("fifo create error");
        exit(1);
    }
    if (mkfifo(name2, S_IRUSR | S_IWUSR) == -1) //jak plik, czyli dawa razy nie możemy utworzyć dwa razy
    {
        perror("fifo create error");
        exit(1);
    }
    if (fork() == 0) 
    {
        if ((fd = open(name1, O_WRONLY)) == -1) 
        {
            perror("child fifo open error");
            exit(1);
        }
        dup2(fd, 1);
        execlp("ls", "ls", "-l", NULL);
    } 
    else if (fork() == 0) 
    {
        if ((fd1 = open(name1, O_RDONLY)) == -1) 
        {
            perror("child fifo open error");
            exit(1);
        }
        if ((fd = open(name2, O_WRONLY)) == -1) 
        {
            perror("child fifo open error");
            exit(1);
        }
        dup2(fd1, 0);
        dup2(fd, 1);
        execlp("grep", "grep", "^d", NULL);
    } 
    else 
    {
        if ((fd = open(name2, O_RDONLY)) == -1) 
        {
            perror("parent mkfifo error");
            exit(1);
        }
        dup2(fd, 0);
        execlp("more", "more", NULL);
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
    unlink(name1);
    unlink(name2);
    
}
