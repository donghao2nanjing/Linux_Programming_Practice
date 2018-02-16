// To show how to redirect output for another program
#include <stdio.h>
#include <unistd.h>

main(){
    int pid ;
    int fd ;
    printf("About to run who into a file:\n") ;

    if( (pid =fork()) == -1 ){
        perror("fork error!\n");
        exit(1);
    }

    // Chile process ;
    if( pid == 0){
        close(1); // close fd of stdout
        fd = creat("userlist.txt", 0644); // open to make a new file for default 
        execlp("who", "who", NULL ) ;
        perror("execlp\n");
        exit(1);
    }

    // Parent waits and the reports the result ;
    if(pid == 1 ){
        wait(NULL);
        printf("Done runing who. results in userlist.txt\n");
    }
}