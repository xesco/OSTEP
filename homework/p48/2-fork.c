#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <assert.h>
#include <string.h>
#include <sys/wait.h>

#define LOOP 1000

int
main(int argc, char *argv[]) {
    char *strp = "I am the parent!\n";
    char *strc = "I am the child!\n";

    int fd = open("./newfile.txt", O_WRONLY|O_CREAT|O_TRUNC, S_IRWXU);
    assert(fd>-1);
    
    int rc = fork();
    if (rc < 0) {
        fprintf(stderr, "fork() failed\n");
    } else if (rc == 0) {
        int i = 0;
        while(i++ < LOOP)
            write(fd, strc, strlen(strc));
    } else {
        int i = 0;
        while(i++ < LOOP)
            write(fd, strp, strlen(strp));
    }
}
