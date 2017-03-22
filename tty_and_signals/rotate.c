/* rotate.c
 * purpose:useful for showing tty modes
 * map a->b , b->c , ... , y->z ;
 */
 
 #include <stdio.h>
 #include <stdlib.h>
 #include <ctype.h>
 
 int main()
 {
     int c ;
     while( ( c = getchar()) != EOF )
     {
         if(c == 'z')
         {
             c = 'a';
         }
         else if( islower(c))
         {
             c++ ;
         }
         putchar(c) ;
     }
     return 0 ;
 }