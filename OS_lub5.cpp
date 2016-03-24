#include <string.h>;
#include <fcntl.h>;
#include <vector>;
#include <unistd.h>
#include <iostream>
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

int main(int argc, char *argv[])
{

    int n = 0;
    int s = 0;
    Str tmp();
    std::vector<Str> arr;
    int input_file = 0;
    input_file = open("in.txt", O_RDONLY);
    if(input_file<0){
        std::cout << "We are sorry, but we can't fund this file" << std::endl;
        return 0;
    }
    char buff[1024];
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
    std::cout << "Enter number of string from 1 for " << arr.size() << ": ";
    std::cin >> n;
    if(n == 0){
        std::cout << "The end." << std::endl;
    }
    if(n<0 || n>arr.size()){
        std::cout << "We are sorry, but this line doesn't exist" << std::endl;
        return 0;
    }
    lseek(input_file,arr[n-1].GetPos(),0);
    for(int i=0; i< arr[n-1].GetNum(); i++) {
        read(input_file, buff, 1);
        std::cout << buff;
    }
    std::cout << std::endl;
    close(input_file);
    return 0;
}
