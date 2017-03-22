#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#define INPUTLEN 100


int main()
{
    struct sigaction newhandler ;
    sigset_t    blocked ;
    void        inthandler();
    char        x[INPUTLEN] ;

    newhandler.sa_handler = inthandler ;
    newhandler.sa_flags = SA_RESETHAND | SA_RESTART ;

    sigemptyset(&blocked);

    sigaddset(&blocked, SIGQUIT);

    newhandler.sa_mask = blocked ;

    if(sigaction(SIGINT, &newhandler, NULL) == -1)
    {
        perror("sigaction error\n");
    }
    else
    {
        while(1)
        {
            fgets(x, INPUTLEN, stdin ) ;
            printf("Input:%s", x);
        }
    }
    return 0 ;
}

void inthandler(int s)
{
    printf("Call with Signal:%d\n", s);
    sleep(s) ;
    printf("Done with Signal:%d\n", s) ;
}
