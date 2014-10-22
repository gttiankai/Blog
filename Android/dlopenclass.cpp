/* 该文件是为了实现通过dlopen和dlsym())来对动态库中函数进行调用,
 * 需要注意的是 本次实验的是 动态库中的文件都是 使用cpp文件的,面向对象的方法写成的.
 * 编译命令: g++ -m32 dlopenclass.c -o dlopenclass -ldl
 * 验证的结论: 可以通过这种方法调用类中的构造函数,static方法, public方法,还有private方法.
 * 需要注意的问题: 我们在调用类中的方法的时候,首先也要调用类的构造方法,创建对象,然后将该对象作为类方法的第一个参数传递给指针.
 */
#include <dlfcn.h>
#include <stdio.h>
#include <cstdlib>
#include "Helloworld.h"
int main (int argc, char const *argv[])
{
    /* code */
    //"/lib/i386-linux-gnu/libdl.so.2"
    //const char* path = "/home/tiankai/temp/hellodlopen.so";
    const char* path = "/home/tiankai/git-hub/Blog/Android/Helloworld.so";
    //const char* functionname = "_Z11helloprintfv";
    const char* functionname_create = "_ZN10HelloworldC2Ei";
    const char* functionname_printf = "_ZN10Helloworld11helloprintfEv";
    void* handle = dlopen(path, RTLD_NOW);
    if( NULL == handle)
    {
        /* code */
        printf("dlopen the so fialed!\n");
    };
    //int (*pointer_printf)(__const char *__restrict __formate, ...);
    //void (*pointer)( Helloworld* ); // 定义helloprintf的函数指针
    void (*create)(Helloworld *, int);
    //pointer_printf = (int (*)(__const char *__restrict __formate, ...))dlsym(handle,functionname);
    create = ( void(*)(Helloworld*, int) )dlsym(handle, functionname_create);
    if (create == NULL)
    {
        printf("dlsym the create failed!\n");
    }
    Helloworld* hello = (Helloworld *)malloc(sizeof(Helloworld));
    create(hello, 2);

    void (*hello_printf)(Helloworld *);

    hello_printf = (void(*)(Helloworld *))dlsym(handle, functionname_printf);

    if(hello_printf == NULL){
        printf("dlsym the printf failed!");
    }
    hello_printf(hello);
    //(*pointer_printf)("hellodlopen\n");
    free(hello);
    dlclose(handle);
    return 0;
}
