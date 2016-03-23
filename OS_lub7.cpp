#include <unistd.h>
#include <signal.h>
#include<stdlib.h>
#include <iostream>
#include <vector>
std::vector<std::string> str;
void  ALARMhandler(int sig)
{
   signal(SIGALRM, SIG_IGN);          /* ignore this signal       */
   for(int i=0; i<str.size(); i++){
       std::cout << std::endl << str[i] << std::endl;
   }
   signal(SIGALRM, ALARMhandler);     /* reinstall the handler    */
   exit(1);
}

int main()
{

   FILE *fp;
   char buffer;
   //memset(buffer,0,30);
   int n;
   fp = fopen("in.txt", "r");
   str.insert(str.end(),"");
   while(!feof(fp)){
       fscanf(fp, "%c", &buffer);
       if(buffer == '\n'){
           str.insert(str.end(),"");
           continue;
       }
       str[(str.size()-1)] = str[(str.size()-1)] + buffer;
   }
   fclose(fp);
   std::cout << "Enter number of string from 1 for " << str.size() << "(you have 5 sec): ";
   signal(SIGALRM, ALARMhandler);
   alarm(5);
   if(scanf("%d", &n)!=EOF) {
       std::cout << str[(n-1)] << std::endl;
   }

   return 0;
}

