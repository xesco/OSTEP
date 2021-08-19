#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int
main(int argc, char *argv[]) {
    int rc;
    if ((rc = fork()) == -1) {
        perror("fork()");
        exit(EXIT_FAILURE);
    } else if (rc == 0) {
        //char *args[] = {"ls", "-l", "-a", NULL};
        char *args[] = {"/bin/bash", "-c", "env", NULL};
        char *env[]  = {"NAME=Francesc", "SURNAME=Vendrell", NULL};
        //execl("/bin/ls", "ls", "-l", "-a", NULL);
        //execvp("ls", args);
        if ((execve(argv[0], args, env) == -1)) {
            perror("execve");
            exit(EXIT_FAILURE);
        }
    } else {
        wait(NULL);
    }

    return 0;
}
