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

int main()
{
	char name[] = "sefifo", *namecl[16];
    	int fdc,fds, n, i, o, a;
    	char buf[1024], * arguments[10];
    	bool on = true;
    	
	unlink(name1);
	unlink(name2);
	if (mkfifo(name1, S_IRUSR | S_IWUSR) == -1) 
    	{
        	perror("fifo create error");
        	exit(1);
    	}	
	if ((fds = open(name, O_RDONLY)) == -1) 
	{
		perror("server fifo open error");
		exit(1);
	}

	while(on)
	{
		if(n = read(fds, buf, 1024) > 0)
		{
			i = 0;
			o = 0;
			while(buf[i] != '@')		
			{	
				namecl[i] = buf[i];	//szukamy nazwy fifo klienta 
				i++;
			}
			buf[i] = namecl[i] = '\0';
			i++;

			for(i;  buf[i]!= '\n'; i++)
			{
            
               			 if(buf[i] == ' ')
               			 {
                   			 buf[i] = '\0';
                    			arguments[o] = &buf[i+1];
                    			o++;
                		}
               
            		}
			
			
		}
		
		
	*******************************
	if ((fdc = open(namecl, O_RDWR)) == -1) 
	{
		perror("client fifo open error");
		exit(1);
	}

	if ((p = fork()) == 0) 
            {
            	a = dup(1); 
		dup2(1, fdc);
                execvp(arguments[0], arguments); /printf("sss");
                exit(-1);
            }
            else
            {
                wait(&status);
                if(WEXITSTATUS(status) != EXIT_SUCCESS)
                    printf("Wrong command!\n");
            }
	dup2(a, 1);


	}
	unlink(name1);
	unlink(name2);
}
