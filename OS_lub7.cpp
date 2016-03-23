#include<stdio.h>
#include <vector>;
#include <unistd.h>
#include <signal.h>
#include<stdlib.h>
#include <iostream>
std::vector<std::string> str;
void  ALARMhandler(int sig)
{
   signal(SIGALRM, SIG_IGN);          /* ignore this signal       */
   std::cout << std::endl;
   for(int i=0; i<str.size(); i++){
       std::cout << str[i] << std::endl;
   }
   signal(SIGALRM, ALARMhandler);     /* reinstall the handler    */
   exit(1);
}

int main()
{

   FILE *fp;
   char buffer;
   int n;
   fp = fopen("in.txt", "r");
   str.insert(str.end(),"");
   while(!feof(fp) && buffer!=EOF){
       buffer = fgetc(fp);
       if(feof(fp) || (buffer==EOF)){
           str.pop_back();
           break;
       }
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
