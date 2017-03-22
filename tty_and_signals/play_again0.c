/* play_again0.c
 * purpuse: ask if user wants another play 
 * returns: 0 -> yes , 1 -> no 
 */
 
 #include <stdio.h>
 #include <stdlib.h>
 #include <termios.h>
 
 #define QUESTION "Do you want another play?"
 
 int get_response(char *);
 
 int main()
 {
     int response ;
     response = get_response(QUESTION);
     return response ;
 }
 
 int get_response(char * qiz)
 {
     printf("%s(y/n)" , qiz);
     while(1)
     {
         switch(getchar())
         {
             case 'y':
             case 'Y': return 0 ;
             case 'n': 
             case 'N': return 1 ;
         }
     }
 }