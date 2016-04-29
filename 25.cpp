#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include<ctype.h>
#include <string.h>
#define SIZE 100
int main(int argc, char* argv[]) {
  pid_t pid;
  int rv;
  int fd[2];
  char buffer[SIZE] = "fghsdk F hgkddDFFhgdfgk shdgshd";
  char chars[SIZE];
        if(-1 == pipe(fd))
        {
                perror("pipe");
                exit(1);
        }
 if( !fork() )
  {
        write(fd[1],buffer,SIZE-1);
                    if(-1 == close(fd[1]))
                    {
                            perror("close");
                            exit(3);
                    }
                    exit(0);
  }
   if( !fork() )
    {
       read(fd[0],chars,SIZE-1);
             for(int i=0; strlen(chars)>i; i++)
            {
                      chars[i] = toupper(chars[i]);
            }
             printf("%s\n",chars);
  }
        if(-1 == close(fd[0]))
        {
                perror("close");
                exit(4);
        }
  return 0;
}


