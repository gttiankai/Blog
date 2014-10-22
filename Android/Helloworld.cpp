#include <iostream>
<<<<<<< HEAD
class Helloworld
{
public:
    Helloworld();
    virtual ~Helloworld();
    void printf(){
        std::cout<<"hello dlopen!"<<std::endl;
    }
};
int main(int argc, char *argv[])
{
    Helloworld hello;
    hello.printf();
    return 0;
}
=======
#include "Helloworld.h"
//#include <stdio.h>
Helloworld::Helloworld(int b){
    this->a = b;
    //std::cout<<"Helloworld construct "<<std::endl;
}
void Helloworld::helloprintf(){
    std::cout<<a<<std::endl;
    //return a;
}
//int main(int argc, char *argv[])
//{ 
//    Helloworld hello;
//    Helloworld(&hello, 1);
//    hello.helloprintf();
//    return 0;
//} 
>>>>>>> change the Android/Helloworld.cpp
