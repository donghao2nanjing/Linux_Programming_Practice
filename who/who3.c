/*Apply a Buffer trick in who3.c*/

#include <stdio.h>
#include <stdlib.h>
#include <utmp.h>
#include <fcntl.h>
#include <unistd.h>
#include <time.h>

#define NRECS 16
#define NULLUT ((struct utmp * ) NULL )
#define UTSIZE (sizeof(struct utmp))

#define SHOWHOST	

static char utmpbuf[NRECS * UTSIZE] ;
static int  num_recs ;
static int  cur_rec ;
static int fd_utmp = -1 ;

void show_info(struct utmp * utbufp) ;
void show_time(time_t timeval);

int utmp_open(char *);
int utmp_reload(void);
struct utmp * utmp_next(void);
void utmp_close(void);

int main(){ 
	struct utmp * utbufp ;
	struct utmp * utmp_next() ;

	if( utmp_open( UTMP_FILE ) == -1 ){
		perror(UTMP_FILE );
		exit(1);
	}

	while( (utbufp = utmp_next()) != ((struct utmp * ) NULL)){
		show_info(utbufp);
	}

	utmp_close();
	return 0 ;

}

void show_info(struct utmp * utbufp ){
	if( utbufp->ut_type != USER_PROCESS)
		return;

	printf("%-8.8s" , utbufp->ut_name );
	printf(" ");
	printf("%-8.8d" , utbufp->ut_type );
	printf(" ");
	printf("%-8.8s" , utbufp->ut_line);
	printf(" ");
	show_time(utbufp->ut_time);

#ifdef SHOWHOST
	printf("(%s)", utbufp->ut_host);
#endif
	printf("\n");
	//printf("One Done!\n");

}

void show_time(long timeval)
{
	char * cp ;
	cp = ctime(& timeval);
	printf("%12.12s" , cp + 4 );
}

int utmp_open( char * filename ){
	fd_utmp = open(filename , O_RDONLY );
}

struct utmp * utmp_next(void){
	struct utmp * recp ;
	if( fd_utmp == -1 ){
		return NULLUT ;
	}
	if( cur_rec == num_recs && utmp_reload() == 0 ){
		return NULLUT ;
	}

	recp = (struct utmp * ) & utmpbuf[cur_rec * UTSIZE];
	cur_rec ++ ;
	return recp ;
}

int utmp_reload(void)
{
	int amt_read ; // file read , fd 
	amt_read = read(fd_utmp , utmpbuf , NRECS * UTSIZE );
	num_recs = amt_read/UTSIZE ;
	cur_rec = 0 ;
	return num_recs ;
}

void utmp_close(void){
	if(fd_utmp != -1 ){
		close(fd_utmp );
	}
}

