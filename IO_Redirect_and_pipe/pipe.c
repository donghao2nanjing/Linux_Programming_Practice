// This is a pipe between two process 
// pipe stdout -> stdin 
// e.g. pipe who sort
// e.g. pipe ls head 

#include <stdio.h>
#include <unistd.h>

#define oops(m,x)   {perror(m); exit(x);}

main(int ac, char * av[]){
    int thepipe[2];
    int newfd ;
    int pid ;

    if(ac != 3){
        fprintf(stderr, "usage:pipe cmdl1 cmd2\n");
        exit(1);
    }

    if(pipe(thepipe) == -1){
        oops("Cannot get a pipe!\n", 1);
    }

    if( (pid = fork()) == -1 ){
        oops("Cannot fork!\n", 2);
    }

    // Parent process 
    if( pid > 0){
        close(thepipe[1]); // parent does not write to pipe ;
        if( dup2( thepipe[0], 0) == -1 ){
            oops("Could not redirect stdin to pipe", 3);
        }
        close( thepipe[0]); // stdin is duped, close the pipe ;
        execlp(av[2], av[2], NULL); // 
        oops(av[2], 4);
    }

    // Child process 
    close(thepipe[0]); 
    if( dup2(thepipe[1], 1) == -1){
        oops("Could not redirect stdout", 4);
    }
    close(thepipe[1]);
    execlp(av[1], av[1], NULL);
    oops(av[1], 5);
}