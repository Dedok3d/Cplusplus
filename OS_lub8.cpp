#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>

int main( int argc, char*argv[])
{
   int     file;
   struct flock fstr;

   fstr.l_type   = F_WRLCK;
   fstr.l_whence = SEEK_SET; /*The offset, SEEK_SET - start file */
   fstr.l_start  = 0; /*The starting offset*/
   fstr.l_len    = 0; /*The number of bytes to lock*/
   if(( file = open( "input.txt",O_RDONLY )) == -1)
       /*stderr - the standard error stream*/
       return fprintf(stderr,"Error in opening file \n");
   /*Fcntl using for unlock file*/
   /*F_GETLK - to obtain data on lock*/
   /*F_SETLK - to install capture recording*/
   /*F_SETLKW - to install capture recording (with unlock)*/
   if(fcntl( file, F_SETLK, &fstr )==-1)
   {
       perror("fcntl");
       return 0;
   }
   /*Call vim*/
   system("vi input.txt");
   fstr.l_type = F_UNLCK;
   /*Unlock file*/
   fcntl( file, F_SETLK, &fstr);
   close(file);
   return 0;
}




