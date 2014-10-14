#include <iostream>
class Helloworld
{
public:
    Helloworld();
    virtual ~Helloworld();
    void printf(){
        std::cout<<"hello dlopen!"<<std::endl;
    };
};
int main(int argc, char *argv[])
{
    Helloworld hello;
    hello.printf();
    return 0;
}