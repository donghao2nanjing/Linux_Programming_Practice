// Establish a timeserver locally on port 13000
// Test usage:
// telnet 127.0.0.1 13000
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <time.h>
#include <string.h>

#define PORTNUM 13000 // time service phone number
#define HOSTLEN 256 
#define oops(message) {perror(message); exit(1);}

int main(int ac, char *av[]){
    struct sockaddr_in  saddr ; // socket address 
    struct hostent  * hp ; 
    char hostname[HOSTLEN]; //address 
    int sock_id, sock_fd ;
    FILE * sock_fp ;
    char * ctime(); // convert time seconds to string 
    time_t thetime ; // time to report 

    // Step 1 :
    sock_id = socket(PF_INET, SOCK_STREAM, 0 ); // get a socket ;
    if( sock_id == -1 ){
        oops("Socket");
    }

    // Step 2 : bind address to socket. Address is in the form: address, port 
    bzero( (void * ) & saddr, sizeof(saddr)); // clear out struct

    gethostname( hostname, HOSTLEN);
    hp = gethostbyname(hostname);

    // Attention: h_addr_list, not h_addr
    bcopy( (void * )hp->h_addr_list, (void *)&saddr.sin_addr , hp->h_length) ;
    saddr.sin_port = htons(PORTNUM);
    saddr.sin_family = AF_INET ;

    // Attention here.(https://stackoverflow.com/questions/15488092/bind-failed-cannot-assign-requested-address)
    saddr.sin_addr.s_addr = htonl(INADDR_ANY); // in case of Bind: Cannot assign requested address

    if( bind(sock_id, (struct sockaddr *) &saddr, sizeof(saddr)) != 0)
    {
        oops("Bind");
    }

    // Step 3 : allow incoming calls with Qsize = 1 on socket
    if(listen(sock_id, 1) != 0)
    {
        oops("Listen");
    }

    // Set up ready
    // Main Loop: accept, write, close
    while(1){
        sock_fd = accept(sock_id, NULL, NULL) ; // wait for call 
        printf("Server:Wow, we have got a call!\n");
        if(sock_fd == -1 )
        {
            oops("Accept");
        }

        sock_fp = fdopen(sock_fd, "w");
        if(sock_fp == NULL ){
            oops("fdopen()");
        }

        thetime = time(NULL); // get time 
        
        fprintf(sock_fp, "The time is:");
        fprintf(sock_fp, "%s", ctime(&thetime));
        fclose(sock_fp) ; // Release connection ;
    }

}
