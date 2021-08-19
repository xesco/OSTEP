#include <assert.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

int
main(int argc, char *argv[]) {

    pid_t rc1, rc2;
    int fds[2];

    printf("Parent: Hello world! from PID:%d\n", getpid());

    if(pipe(fds) == -1) {
        perror("pipe()");
        exit(EXIT_FAILURE);
    }

    // creating first process
    if((rc1 = fork()) == -1) {
        perror("fork()");
        exit(EXIT_FAILURE);
    } else if (rc1 == 0) {
        // fd movement
        close(STDOUT_FILENO);
        assert(dup(fds[1]) == STDOUT_FILENO); // setting stdout to fd[1]
        close(fds[1]);
        close(fds[0]); // closing the read end of the pipe

        printf("Child1: Hello world! from PID:%d\n", getpid());
        exit(EXIT_SUCCESS);
    }

    // creating second process
    if((rc2 = fork()) == -1) {
        perror("fork()");
        exit(EXIT_FAILURE);
    } else if (rc2 == 0) {
        // read from stdin
        char *line = NULL;
        size_t len = 0;

        // fd movement
        close(STDIN_FILENO);
        assert(dup(fds[0]) == STDIN_FILENO); // setting stdin to fds[0]
        close(fds[0]);
        close(fds[1]); // closing the write end of the pipe

        printf("Child2: Hello world from PID:%d\n", getpid());

        getline(&line, &len, stdin);
        printf("%s", line);
        free(line);
        exit(EXIT_SUCCESS);
    }

    waitpid(rc1, NULL, 0);
    waitpid(rc2, NULL, 0);
    return(0);
}
