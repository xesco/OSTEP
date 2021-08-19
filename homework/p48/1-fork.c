#include <stdio.h>
#include <unistd.h>

int
main(int argc, char *argv[]) {

    int x = 100;
    int rc = fork();
    if (rc < 0) {
        fprintf(stderr, "fork() failed\n");
    } else if (rc == 0) { // child
        printf("I am the child (pid: %d) and the value of x is: %d\n", (int) getpid(), x);
        x++;
        printf("I am the child (pid: %d) and the value of x is: %d\n", (int) getpid(), x);
        
    } else { // parent
        printf("I am the parent of %d (pid: %d) and the value of x is: %d\n", rc, (int) getpid(), x);
        x++;
        printf("I am the parent of %d (pid: %d) and the value of x is: %d\n", rc, (int) getpid(), x);
    }

    return 0;
}

