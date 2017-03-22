/* play_again3.c
 * purpuse: ask if user wants another play 
 * better : instant response without echo
              set tty into no-delay mode
              read char , return result
              reset terminal mode on Internet
 * returns: 0 -> yes , 1 -> no 
 */
 
 #include <stdio.h>
 #include <stdlib.h>
 #include <fcntl.h>
 #include <termios.h>
 #include <string.h>
 
 #define ASK "Do you want another play?"
 #define TRIES 3
 #define SLEEPTIME 2
 #define BEEP putchar('\a');


 int get_response(char *);
 int get_ok_char(void);
 void set_nodelay_mode(void);
 void set_cr_noecho_mode(void);
 void tty_mode(int); 
 
 int main()
 {
     int response ;
     tty_mode(0);   // save tty mode
     set_cr_noecho_mode();
     set_nodelay_mode();
     response = get_response(ASK);
     tty_mode(1);   // restore tty mode
     return response ;
 }
 
 int get_response(char * qiz)
 {
     int input ;
     int maxtries = TRIES ;
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