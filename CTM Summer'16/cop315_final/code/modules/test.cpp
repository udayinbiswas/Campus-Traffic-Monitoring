#include <unistd.h>
#include <stdio.h>
 
int main(void)
{
     
    printf("I'll be back in 10 seconds...\n\n");
    sleep(10);
    printf("I'm back!");
    getchar();
     
    return(0);
}
