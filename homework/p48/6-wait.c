#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>

int
main(int argc, char *argv[]) {

    pid_t rc;
    if((rc = fork()) == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    } else if (rc == 0) {
        printf("I am the child with PID:%d\n", (int)getpid());
    } else {
        int wrc;
        if((wrc = waitpid(rc, NULL, 0)) == -1) {
            perror("waitpid");
            exit(EXIT_FAILURE);
        }
        printf("I am the parent with PID:%d\n", (int)getpid());
    }

    return 0;
}
