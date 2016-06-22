#include <stdio.h>
int main ()
{
    int a=5;
    int b=6;
    int soma=0;
    int sub=0;
    int mul=0;
    int div=0;
    int flag=0;
    int c[5]= {1,2,3,4,5};
    soma = a+b;
    mul = a*b;
    div = a/b;
    sub = a-b;
    if (a>=b){
        printf("a>=b");
    }
    if (a>b){
        printf ("a>b");
    }
    if (a==b){
        printf ("a==b");
    }
    if (a<=b){
        printf ("a<=b");
    }
    if (a<b){
        printf ("a<b");
    }
    if (a!=b){
        printf ("a!=b");
    }
}

int voidfunc();