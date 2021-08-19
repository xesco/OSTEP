#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int
main(int argc, char *argv[]) {
    int rc = fork();

    if (rc == -1) {
        perror("fork()");
    } else if (rc == 0) {
        printf("Hello\n");
    } else {
        wait(NULL);
        printf("Goodbye\n");
    }

    return 0;
}
