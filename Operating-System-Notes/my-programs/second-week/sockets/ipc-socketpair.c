#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#define DATA1 "Hello World!!"
#define DATA2 "Amazon is at Chennai"

/*
 * This  program creates a  pair of connected sockets,
 * then forks and communicates over them.  This is very 
 * similar to communication with pipes, however, socketpairs
 * are  two-way  communications  objects.  Therefore I can
 * send messages in both directions.
 */

main()
{
    int sockets[2], child;
    char buf[1024];

    if (socketpair(AF_UNIX, SOCK_STREAM, 0, sockets) < 0) {
        perror("opening stream socket pair");
        exit(1);
    }

    if ((child = fork()) == -1)
        perror("fork");
    else if (child) {       /* This is the parent. */
        close(sockets[0]);
        if (read(sockets[1], buf, sizeof(buf)) < 0)
            perror("reading stream message");
        printf("Parent read-->%s\n", buf);
        if (write(sockets[1], DATA2, sizeof(DATA2)) < 0)
            perror("writing stream message");
        close(sockets[1]);
    } else {                /* This is the child. */
        close(sockets[1]);
        if (write(sockets[0], DATA1, sizeof(DATA1)) < 0)
            perror("writing stream message");
        if (read(sockets[0], buf, sizeof(buf)) < 0)
            perror("reading stream message");
        printf("client read-->%s\n",buf); 
        close(sockets[0]);
    }
}
