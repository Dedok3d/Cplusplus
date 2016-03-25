#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
int main()
{
  pid_t pid;
  int rv;
  switch(pid=fork()) {
     case -1:
        perror("fork"); /* error */
        exit(1); /*exit*/
     case 0:
        printf(" CHILD: This is the child process!\n");
        execl("/bin/cat", "cat", "in.txt", (char *)NULL);
     default:
        printf("PARENT: This is the parent process!\n");
        printf("PARENT: my PID -- %d\n", getpid());
        printf("PARENT: My child PID %d\n",pid);
        printf("PARENT: I wait? while my child don't call exit()...\n");
        wait(&rv);
        printf("PARENT: Child retern code:%d\n", WEXITSTATUS(rv));
        printf("PARENT: Exit!\n");
  }
  return 0;
}

