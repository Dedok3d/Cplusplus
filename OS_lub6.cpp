#include <string.h>;
#include <fcntl.h>;
#include<stdio.h>
#include <vector>;
#include <unistd.h>
#include <signal.h>
#include<stdlib.h>
#include <iostream>
char buff[1024];
int input_file = 0;

class Str{
    int startPos;
    int numLet;
public:
    Str(){
        startPos = 0;
        numLet = 0;
    }
    Str(int a, int b){
        startPos = a;
        numLet = b;
    }

    void SetPos(int a){
        startPos = a;
    }

    void SetNum(int b){
        numLet = b;
    }

    int GetPos(){
        return startPos;
    }

    int GetNum(){
        return numLet;
    }
};

void printFile(){
    //int input = open("in.txt", O_RDONLY);
    std::cout << std::endl;
    lseek(input_file,0,0);
    while(read(input_file, buff, 1)) {
        std::cout << buff;
    }
    std::cout << std::endl;

}

void  ALARMhandler(int sig)
{
    signal(SIGALRM, SIG_IGN);          /* ignore this signal       */
    printFile();
    signal(SIGALRM, ALARMhandler);     /* reinstall the handler    */
    exit(1);
}
int main(int argc, char *argv[])
{

    int n = 0;
    int s = 0;
    Str tmp();
    std::vector<Str> arr;

    input_file = open("in.txt", O_RDONLY);
    if(input_file<0){
        std::cout << "We are sorry, but we can't fund this file" << std::endl;
        return 0;
    }

    memset(buff, 0, 1024);
    while(read(input_file, buff, 1)) {
        n++;
        if(buff[0]=='\n') {
            arr.insert(arr.end(),Str(s,(n-s-1)));
            memset(buff, 0, 1024);
            s = n;
        }
    }
    memset(buff, 0, 1024);
    signal(SIGALRM, ALARMhandler);
    std::cout << "Enter number of string from 1 for " << arr.size() << "(you have 5 sec): ";
    alarm(5);
   if(scanf("%d", &n)!=EOF)
   {

       lseek(input_file,arr[n-1].GetPos(),0);
       for(int i=0; i< arr[n-1].GetNum(); i++) {
           read(input_file, buff, 1);
           std::cout << buff;
       }
       std::cout << std::endl;
       close(input_file);
       return 0;
   }

    close(input_file);
    return 0;
}
