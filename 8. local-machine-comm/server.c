#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
 
#define SOCKET_PATH  "/tmp/lab6_pp"
#define BUFFER_SIZE  512
 
static void die(const char *msg)
{
    perror(msg);
    exit(EXIT_FAILURE);
}
 
static void send_cmd(int fd, const char *cmd)
{
    if (send(fd, cmd, strlen(cmd), 0) == -1)
        die("send");
}
 
static void recv_msg(int fd, char *buf, size_t buf_size)
{
    ssize_t n = recv(fd, buf, buf_size - 1, 0);
    if (n == -1) die("recv");
    if (n == 0)  { fprintf(stderr, "Client disconnected unexpectedly.\n"); exit(1); }
    buf[n] = '\0';
}
 
int main(void)
{
    int              server_fd, client_fd;
    struct sockaddr_un addr;
    char             buffer[BUFFER_SIZE];
 
    server_fd = socket(AF_UNIX, SOCK_STREAM, 0);
    if (server_fd == -1) die("socket");
 
    unlink(SOCKET_PATH);
 
    memset(&addr, 0, sizeof(addr));
    addr.sun_family = AF_UNIX;
    strncpy(addr.sun_path, SOCKET_PATH, sizeof(addr.sun_path) - 1);
 
    if (bind(server_fd, (struct sockaddr *)&addr, sizeof(addr)) == -1) {
        close(server_fd);
        die("bind");
    }
 
    if (listen(server_fd, 1) == -1) {
        close(server_fd);
        unlink(SOCKET_PATH);
        die("listen");
    }
 
    printf("Waiting for the client...\n");
    fflush(stdout);
 
    client_fd = accept(server_fd, NULL, NULL);
    if (client_fd == -1) {
        close(server_fd);
        unlink(SOCKET_PATH);
        die("accept");
    }
    printf("client connected to the server\n");
    printf("server: accept()\n");

    printf("The server requests the client's pid\n");
    send_cmd(client_fd, "Pid");
 
    recv_msg(client_fd, buffer, sizeof(buffer));
    printf("server: %s\n", buffer);          // the client's response PID.
 
    printf("The server requests the client to sleep\n");
    send_cmd(client_fd, "Sleep");
 
    recv_msg(client_fd, buffer, sizeof(buffer));  // wait for the client to finish sleeping
 
    printf("The server requests the client to quit\n");
    send_cmd(client_fd, "Quit"); // Tell the client to quit.
 
    close(client_fd);
    close(server_fd);
    unlink(SOCKET_PATH);
 
    return 0;
}