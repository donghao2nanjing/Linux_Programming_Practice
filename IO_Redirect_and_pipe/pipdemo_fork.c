#include <stdio.h>
#include <string.h>
#include <unistd.h>

#define CHILD_MESS  "I want a cookie\n"
#define PAR_MESS    "Testing...\n"
#define oops(m,x)   {perror(m); exit(x);}
//#define BUFSIZ 100 

main(){
    int pipefd[2]; 
    int len ;
    char buf[BUFSIZ] ;
    int read_len ;

    printf("To see size of buf: %d\n", BUFSIZ);

    if( pipe( pipefd) == -1){
        oops("cannot get a pipe\n", 1) ;
    }

    switch(fork()){
        case -1 :
            oops("cannot fork\n", 1);

        case 0 :    // child process ;
            len = strlen(CHILD_MESS);
            while(1){
                if(write( pipefd[1], CHILD_MESS, len) != len){
                    oops("write\n", 3) ;
                }
                sleep(5);
            }
        default:
            len = strlen(PAR_MESS);
            while(1){
                if( write( pipefd[1], PAR_MESS, len) != len){
                    oops("write\n", 4);
                }
                sleep(1);
                read_len = read(pipefd[0], buf, BUFSIZ);
                if( read_len < 0)
                {
                    break ;
                }
                write(1, buf, read_len);
            }

    }
}
