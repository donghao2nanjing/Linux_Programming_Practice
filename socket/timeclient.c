// This is a time client to read time from local server using socket 
// Test usage:
// ./timeclient 127.0.0.1 13000
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdlib.h>
#include <unistd.h>

#define oops(msg) {perror(msg); exit(1);}

main(int ac, char * av[]){
    struct sockaddr_in servadd ;
    struct hostent * hp ;
    int sock_id, sock_fd ;
    char message[BUFSIZ] ;
    int messlen ; 

    // Step 1
    sock_id = socket(AF_INET, SOCK_STREAM, 0); // get a line 
    if(sock_id == -1){
        oops("Socket");
    }

    // Step 2 : connect to server 
    bzero(&servadd, sizeof(servadd));
    hp = gethostbyname(av[1]); // look up hosts ip ;
    if( hp == NULL){
        oops(av[1]);
    }

    bcopy(hp->h_addr_list, (struct sockaddr *)&servadd.sin_addr, hp->h_length);
    servadd.sin_port = htons(atoi(av[2]));
    servadd.sin_family = AF_INET ;
    servadd.sin_addr.s_addr = htonl(INADDR_ANY); 

    if ( connect(sock_id, (struct sockaddr *)&servadd, sizeof(servadd)) != 0){
        oops("connect");
    }

    messlen = read(sock_id, message, BUFSIZ);
    if(messlen == -1){
        oops("read");
    }
    printf("Client:Now print the time from server:\n");
    if(write(1, message, messlen) != messlen){
        oops("write to stdout failed!");
    }
    close(sock_id);
}