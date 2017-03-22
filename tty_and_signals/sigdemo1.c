#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

void f(int) ;

int main()
{
	void f(int) ;
	int i ;

	signal(SIGINT , f) ; // Declare the handler

	for(i = 0 ; i < 5 ; i ++ ){
		printf("Hello!\n" );
		sleep(1) ;
	}

	return 0 ;
}

void f(int signum )
{
	printf("OUCH!\n");
}