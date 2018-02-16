// This program is to demonstrate that it is the shell which redirects the IO, not program itself.
// cc listargs.c -o listargs
// ./listargs test1 test2 test3
// ./listargs test1 test2 test3 > content_redirected 2> stderr_redirected
#include <stdio.h>

main(int ac, char * av[])
{
    int i ;
    printf("Number of args: %d\n Args are:\n", ac );
    for (i = 0 ; i < ac; i ++ ){
        printf("args[%d]:%s\n", i, av[i]);
    }
    fprintf(stderr, "This is printed to stderr.\n");
}