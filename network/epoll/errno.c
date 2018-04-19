#include <errno.h>  
#include <string.h>  
#include <stdio.h>  
  
int main()  
{  
    int i;  
    for(i = 0; i < 140; ++i)  
    {  
        errno = i;  
        printf("errno %d :\t\t%s\n",i,strerror(errno));  
    }  
    return 0;  
}  
