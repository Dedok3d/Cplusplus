#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include<iostream>
#include <stdlib.h>
#include <wait.h>

int main(int argc, char* argv[])
{
	pid_t pid;
	int status = 0;

	if (argc < 2)
	{
		printf("%s","It's error, please use like ./a.out [command_name] [parametrs]");
		exit(-1);
	}

	switch (pid = fork()) {
	case -1:
		//perror("fork"); /* error */
		exit(1); /*exit*/
	case 0: 
		printf(" CHILD: This is the child process!\n");
		execvp(argv[1], &argv[1]);
		perror("CHILD error");
		exit(2);
	default: 
		if (wait(&status) == -1)
			exit(2);
		printf("PARENT: Exit!\n");
	}

	printf("Exit code = %d\n", WEXITSTATUS(status));
	return 0;
}
