/* 该段代码的作用就是学习一下函数指针的使用,个人感觉函数指针还是非常强大的,
 * 在某些情况下,只有函数指针才能够解决问题.
 *
 *
 *
 *
 *
 *
 */

/* 本例子是说明使用函数指针作为返回值
 *
 *
 *
 */
#include <iostream>
#include <string.h>
#include <stdio.h>
float add(float a, float b){return a + b;}
float minus(float a, float b){ return a - b;}
float multiply(float a, float b){ return a*b;}
float divide(float a, float b){return a/b;}

float ( * functionMap(char op) )(float, float)
{

    switch (op) {
        case '+':
            return add;
            break;
        case '-':
            return minus;
            break;
        case '*':
            return multiply;
            break;
        case '/':
            return divide;
            break;
    }
}
int main(int argc, char *argv[])
{
    float a = 10, b = 5;
    char ops[] = {'+', '-', '*', '/'};
    int len = strlen(ops);

    // 定义函数指针
    float (*returned_function_pointer)(float, float);
    
    for (int i = 0; i < len; ++i)
    {
        returned_function_pointer = functionMap(ops[i]);
        printf("the result caculated by the operator %c is %f \n", ops[i],
            returned_function_pointer(a, b));
    }
    return 0;
}