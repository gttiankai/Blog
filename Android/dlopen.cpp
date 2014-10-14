/* 该文件是为了实现通过dlopen和dlsym())来对动态库中函数进行调用,本程序只是为了模拟这个过程.
 * 功能:通过加载libc.so这个库,调用dlopen和dlsym来调用printf,打印"HelloDlopen"
 * 编译命令: g++ -ldl -m32 dlopen.c -o dlopen
 * 编译时候遇到的问题: 1.main.cpp:(.text+0x19): undefined reference to `dlopen'
 *         解决办法: 将 -ldl 放在编译命令的最后面,正确的命令是:g++ -m32 dlopen.c -o dlopen -ldl
 *     2. 在编译的时候一定要注意程序是32位的还是64位的问题.
 *
 *
 */
#include <dlfcn.h>
#include <stdio.h>

int main (int argc, char const *argv[])
{
    /* code */
    //"/lib/i386-linux-gnu/libdl.so.2"
    //const char* path = "/home/tiankai/temp/hellodlopen.so";
    const char* path = "/lib32/libc-2.15.so";
    const char* functionname = "printf";
    void* handle = dlopen(path, RTLD_NOW);
    if( NULL == handle)
    {
        /* code */
        printf("dlopen the so fialed!\n");

    };
    int (*pointer_printf)(__const char *__restrict __formate, ...);
    //void (*pointer)();
    pointer_printf = (int (*)(__const char *__restrict __formate, ...))dlsym(handle,functionname);
    //pointer = ( void(*)() )dlsym(handle, functionname);
    if (pointer_printf == NULL)
    {
        printf("dlsym the printf failed!\n");
    }
    //(*pointer)();
    (*pointer_printf)("hellodlopen\n");
    dlclose(handle);
    return 0;
}
