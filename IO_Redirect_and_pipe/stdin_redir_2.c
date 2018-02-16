#include <stdio.h>
#include <fcntl.h>

#define CLOSE_DUP  // 
//#define USE_DUP2 

main(){
    int fd ;
    int new_fd ;
    char line[100] ;

        // read and print 3 lines 
    fgets(line, 100, stdin); printf("%s", line);
    fgets(line, 100, stdin); printf("%s", line);
    fgets(line, 100, stdin); printf("%s", line);

    fd = open("data.txt", O_RDONLY) ;
#ifdef CLOSE_DUP
    close(0) ;
    new_fd = dup(fd);
#else
    new_fd = dup2(fd, 0);
#endif 
    if(new_fd != 0){
        fprintf(stderr, "Could not open data as fd 0\n"); // in case of failure ;
        exit(1) ;
    }
    close(fd) ;

    fgets(line, 100, stdin); printf("%s", line);
    fgets(line, 100, stdin); printf("%s", line);
    fgets(line, 100, stdin); printf("%s", line);

}