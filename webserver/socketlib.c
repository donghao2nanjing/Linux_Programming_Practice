#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <time.h>
#include <string.h>

#define HOSTLEN 256
#define BACKLOG 1

int make_server_socket_q(int pnum, int qnum);

int make_server_socket(int portnum ){
	return make_server_socket_q(portnum, BACKLOG);
}

int make_server_socket_q(int pnum, int qnum){
	struct sockaddr_in saddr ;
	struct hostent * hp ;
	char hostname[HOSTLEN];
	int sock_id ;

	// Get a socket:
	sock_id = socket(PF_INET, SOCK_STREAM, 0);
	if(sock_id == -1 ){
		perror("Socket");
		return -1 ;
	}

	// clear struct
	bzero((void * ) & saddr, sizeof(saddr));
	gethostname(hostname, HOSTLEN);
	hp = gethostbyname(hostname);

	bcopy((void *)hp->h_addr_list, (void * )&saddr.sin_addr, hp->h_length);
	saddr.sin_port = htons(pnum);
	saddr.sin_family = AF_INET ;
    saddr.sin_addr.s_addr = htonl(INADDR_ANY);

	if( bind( sock_id, (struct sockaddr *) &saddr, sizeof(saddr)) != 0 ){
		perror("Bind");
		return -1 ;
	}
	if(listen(sock_id, qnum) != 0 ){
		perror("Listen");
		return -1 ;
	}
	return sock_id ;

}

int connect_to_server(char * host, int pnum){
	int sock ;
	struct sockaddr_in servadd ;
	struct hostent * hp ;
	// 1, Get a socket :
	sock = socket(AF_INET, SOCK_STREAM, 0);
	if (sock == -1){
		return -1 ;
	}

	// 2, Connect to server:
	bzero(&servadd, sizeof(servadd));
	hp = gethostbyname(host);
	if(hp == NULL ){
		return -1 ;
	}
	bcopy(hp->h_addr_list, (struct sockaddr * )&servadd.sin_addr, hp->h_length);
	servadd.sin_port = htons(pnum);
	servadd.sin_family = AF_INET ;
	if( connect(sock, (struct sockaddr *)&servadd, sizeof(servadd)) != 0){
		return -1 ;
	}
	return sock ;
}
