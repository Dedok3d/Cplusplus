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
        char buffer[SIZE];
        int readed, i;
        while(0<(readed = read(fileno(stdin),buffer,SIZE)))
        {
                for(i = 0; readed>i; i++)
                {
                        buffer[i] = toupper(buffer[i]);
                }
                write(fileno(stdout),buffer,readed);
        }
        printf("\n");
}


                
