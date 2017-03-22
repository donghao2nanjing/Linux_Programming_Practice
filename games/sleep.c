#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

void wakeup(int signum);

int main()
{
	printf("About to sleep for 4 seconds.\n" );
	signal(SIGALRM , wakeup );
	alarm(4);
	pause();
	printf("Morning so soon ? \n" );
}

void wakeup(int signum)
{
	printf("Alarm received from kernel.\n");
}