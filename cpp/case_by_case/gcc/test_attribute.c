#include <stdio.h>
#include <stdlib.h>
 
static  __attribute__((constructor)) void before()
{
 
    printf("Hello");
}
 
static  __attribute__((destructor)) void after()
{
    printf(" World!\n");
}
 
int main(int args,char ** argv)
{
 
    return EXIT_SUCCESS;
}
