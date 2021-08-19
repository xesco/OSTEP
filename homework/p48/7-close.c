#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int
main(int argc, char *argv[]) {
    pid_t pid;

    if((pid = fork()) == -1) {
        perror("fork()");
        exit(EXIT_FAILURE);
    } else if(pid == 0) {
        // closing stdout
        if((close(STDOUT_FILENO)) == -1) {
            perror("close()");
            exit(EXIT_FAILURE);
        }
        fprintf(stdout, "This won't be printed\n");
    } else {
        fprintf(stdout, "This will be printed\n");
    }
}
