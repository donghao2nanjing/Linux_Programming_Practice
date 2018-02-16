// This demo is to show the pipe in a process itself

#include <stdio.h>
#include <unistd.h>
#include <string.h>

//#define BUFSIZ 100 

main(){
    int len, i, apipe[2] ;
    char buf[BUFSIZ];

    // get a pipe 
    if( pipe(apipe) == -1){
        perror("Could not make pipe\n");
        exit(1);
    }

    printf("Got a pipe! File descriptors:%d, %d\n", apipe[0], apipe[1]);

    while( fgets(buf, BUFSIZE, stdin)){
        len = strlen(buf) ;
        if( write( apipe[1], buf, len) != len){ // send 
            perror("writing to pipe\n");        // to pipe
            break ;
        }

        for (i = 0 ; i < len; i ++){        // clear the chars in buf array
            buf[i] = 'X';
        }

        len = read(apipe[0], buf, BUFSIZE); // read
        if(len == -1 ){                     // from 
            perror("reading from pipe\n");  // pipe
            break ;
        }

        if( write(1, buf, len ) != len){    // print 
            perror("writing to stdout\n");  // to stdout -> screen
            break ;
        }
    }

}