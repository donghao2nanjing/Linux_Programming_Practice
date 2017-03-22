/* play_again1.c
 * purpuse: ask if user wants another play 
 * better : instant response without echo
 * returns: 0 -> yes , 1 -> no 
 */
 
 #include <stdio.h>
 #include <stdlib.h>
 #include <termios.h>
 
 #define QUESTION "Do you want another play?"
 
 int get_response(char *);
 void set_cr_noecho_mode(void);
 void tty_mode(int); 
 
 int main()
 {
     int response ;
     tty_mode(0);   // save tty mode
     set_cr_noecho_mode();
     response = get_response(QUESTION);
     tty_mode(1);   // restore tty mode
     return response ;
 }
 
 int get_response(char * qiz)
 {
     int input ;
     printf("%s(y/n)" , qiz);
     while(1)
     {
         switch(input = getchar())
         {
             case 'y':
             case 'Y': 
                printf("\n");
                return 0 ;
             case 'n': 
             case 'N': 
             case EOF: 
                printf("\n");
                return 1 ;
             default : 
                printf("\nCannot understand %c" , input );
                printf("Please type y or no \n");        
         }
     }
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