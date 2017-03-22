/* set-echo.c 
 * usage : set-echo [y|n]
 * 驱动程序和驱动程序的设置被存储在内核，而不是进程
 × 一个进程可以改变驱动程序里的设置，另一个不同的进程可以读取或修改设置
 */
#include <stdio.h>
#include <stdlib.h>
#include <termios.h>

#define oops(s,x) {perror(s);exit(x);}

int main(int ac , char * av[])
{
    struct termios info ;
    if(ac == 1)
    {
        exit(0);
    }
    if(tcgetattr(0 , &info) == -1 )
    {
        oops("tcsetattr" , 1 );
    }
    if( av[1][0] == 'y')
    {
        info.c_lflag |= ECHO ;
    }
    else
    {
        info.c_lflag &= ~ECHO ;
    }
    
    if(tcsetattr(0 , TCSANOW , &info) == -1 )
    {
        oops("tcsetattr" , 2 );
    }
    
    return 0 ;
}