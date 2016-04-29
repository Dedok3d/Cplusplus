#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include<ctype.h>
#include <string.h>
#define SIZE 100

int main()
{
        char text[SIZE] = "Lalo!IamVaSa!IfRomMorDor!sldselLHlhlFN";
        FILE* ch;
        int i;
        if(0 == (ch = popen("./lab26.2","w")))
        {
                perror("popen");
                exit(1);
        }
        fputs(text, ch);
        if(-1 == pclose(ch))
        {
                perror("pclose");
                exit(2);
        }
}
