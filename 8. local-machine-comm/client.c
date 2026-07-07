#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 
#define SOCKET_PATH  "/tmp/lab6_pp"
#define BUFFER_SIZE  512
 
static void die(const char *msg)
{
    perror(msg);
    exit(EXIT_FAILURE);
}
 
int main(void)
{
    int              sock_fd;
    struct sockaddr_un addr;
    char             cmd[BUFFER_SIZE];
    char             response[BUFFER_SIZE];
    ssize_t          n;
 
    sock_fd = socket(AF_UNIX, SOCK_STREAM, 0);
    if (sock_fd == -1) die("socket");
 
    memset(&addr, 0, sizeof(addr));
    addr.sun_family = AF_UNIX;
    strncpy(addr.sun_path, SOCKET_PATH, sizeof(addr.sun_path) - 1);
 
    if (connect(sock_fd, (struct sockaddr *)&addr, sizeof(addr)) == -1) {
        close(sock_fd);
        die("connect");
    }
 
    while (1) {
 
        n = recv(sock_fd, cmd, sizeof(cmd) - 1, 0);
        if (n == -1) {
            perror("recv");
            break;
        }
        if (n == 0) {
            printf("Server closed the connection.\n");
            break;
        }
        cmd[n] = '\0';
 
        if (strncmp(cmd, "Pid", 3) == 0) {
            printf("A request for the client's pid has been received\n");
 
            pid_t pid = getpid();
            snprintf(response, sizeof(response),
                     "This client has pid %d", (int)pid);
 
            if (send(sock_fd, response, strlen(response), 0) == -1) {
                perror("send pid");
                break;
            }

        } else if (strncmp(cmd, "Sleep", 5) == 0) {
            printf("This client is going to sleep for 5 seconds\n");
            fflush(stdout);
 
            sleep(5);
 
            if (send(sock_fd, "Done", 4, 0) == -1) {
                perror("send Done");
                break;
            }
 
        } else if (strncmp(cmd, "Quit", 4) == 0) {
            printf("This client is quitting\n");
            break;
 
        } else {
            fprintf(stderr, "Unknown command received: %s\n", cmd);
        }
    }

    close(sock_fd);
    return 0;
}