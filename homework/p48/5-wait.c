#include <stdio.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <unistd.h>
#include <assert.h>

int
main(int argc, char *argv[]) {
    int rc;
    if((rc = fork()) == -1) {
        perror("fork()");
        exit(EXIT_FAILURE);
    } else if(rc == 0) {
        if(wait(NULL) == -1) {
            perror("Error wait()");
            exit(EXIT_FAILURE);
        }
        printf("I am the child (pid: %d)\n", getpid());
    } else {
        int rcw = wait(NULL);
        assert(rcw == rc);
        printf("I am the parent (pid: %d) of %d\n", getpid(), rc);
        printf("Child returned with code %d\n", rcw);
    }

    return 0;
}
