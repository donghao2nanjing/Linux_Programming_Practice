/* play_again4.c
 * When no is input , restore the tty settings
 */

 #include <stdio.h>
 #include <termios.h>
 #include <fcntl.h>
 #include <string.h>
 #include <signal.h>
 #include <stdlib.h>

 #define ASK "Do you want to play again?"
 #define TRIES 3
 #define SLEEPTIME 2
 #define BEEP putchar('\a');

void ctrl_c_handler(int);
int get_response(char * , int );
int get_ok_char(void);
void set_nodelay_mode(void);
void set_cr_noecho_mode(void);
void tty_mode(int); 

 int main()
 {
 	int response ;
 	tty_mode(0);
 	set_cr_noecho_mode();
 	set_nodelay_mode();

 	signal(SIGINT , ctrl_c_handler) ; // Set signal responding function
 	signal(SIGQUIT , SIG_IGN );

 	response = get_response(ASK , TRIES );

 	tty_mode(1);
 	return response ;
 }

void ctrl_c_handler(int signum )
{
	tty_mode(1) ; // Restore the tty settings 
	exit(1) ;
}

 int get_response(char * qiz , int tries )
 {
     int input ;
     int maxtries = tries ;
     printf("%s(y/n)" , qiz);
     fflush(stdout);
     while(1)
     {
        BEEP ;
        sleep(SLEEPTIME);
        input = tolower(get_ok_char()) ;
        if(input == 'y')
        {
            printf("\n");
            return 0 ;
        }
        if(input == 'n')
        {
            printf("\n");
            return 1 ;
        }
        if(maxtries -- <= 0 )
        {
            printf("\n");
            return 2 ;
        }
        BEEP ;
     }
 }
 
int get_ok_char(void)
{
    int c ;
    while( (c = getchar() ) != EOF && strchr("yYnN" , c ) == NULL )
        ;
    return c ;
}

void set_cr_noecho_mode(void)
{
    struct  termios ttystate ;
    tcgetattr(0 , &ttystate);
    ttystate.c_lflag &= ~ICANON ;   // No Buffering
    ttystate.c_lflag &= ~ECHO ;
    ttystate.c_cc[VMIN] = 1 ;   //Get one char one time 
    tcsetattr( 0 , TCSANOW , &ttystate);    
}

void set_nodelay_mode(void)
{
    int termflags ;
    termflags = fcntl(0 , F_GETFL);
    termflags |= O_NDELAY ;
    fcntl(0 , F_SETFL , termflags) ;
}

void tty_mode(int mode)
{
    static struct termios original_mode ;// 设置静态结构体变量
    if(mode == 0 )
    {
        tcgetattr( 0 , & original_mode);// 存储原有设置
    }
    else
    {
        //还原原有设置
        if( tcsetattr(0 , TCSANOW , & original_mode) == -1 )
        {
            perror("Restore tty settings failed!\n");
        }
    }
}