// close then open
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>

void main(){
    int fd ;
    char line[100] ;

    // read and print 3 lines 
    fgets(line, 100, stdin); printf("%s", line);
    fgets(line, 100, stdin); printf("%s", line);
    fgets(line, 100, stdin); printf("%s", line);

    close(0); // close stdin 
    fd = open("/etc/passwd", O_RDONLY);
    if(fd != 0){
        fprintf(stderr, "Could not open data as fd 0\n"); // in case of failure ;
        exit(1) ;
    }

    fgets(line, 100, stdin); printf("%s", line);
    fgets(line, 100, stdin); printf("%s", line);
    fgets(line, 100, stdin); printf("%s", line);
}