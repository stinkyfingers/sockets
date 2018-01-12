#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/un.h>

char *socket_path = "/tmp/fast.sock";


int main(int argc, char *argv[]) {

    struct sockaddr_un serv_addr;
    char buf[100];
    int server_fd, cl, rc;

    if ((server_fd = socket(AF_LOCAL, SOCK_STREAM, 0)) < 0) {
        perror("error creating socket"); 
        exit(1);
    }
    

    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sun_family = AF_LOCAL;

    unlink(socket_path);

    bzero(&serv_addr, sizeof(struct sockaddr_un)); // ??

    strcpy(serv_addr.sun_path, socket_path);

    if (bind(server_fd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) == -1) {
        perror("bind"); 
        exit(1);
    }
    if (listen(server_fd, 5) < 0) {
        perror("listen"); 
        exit(1);
    }

    while(1) {
        if ((cl = accept(server_fd, NULL, NULL)) < 0) {
            perror("accept"); exit(1);
        }
        while((rc=read(cl, buf, sizeof(buf))) > 0) {
            printf("read %u bytes: %s\n.", rc, buf);
        }
        if (rc < 0) {
            perror("read"); exit(1);
        }
        if (rc == 0) {
            printf("EOF\n"); close(cl);
        }
    }
    close(server_fd);
    unlink(socket_path);

    return 0;

    // TODO dgram 
    // while (1) {
    //     int bytes_rec = 0;
    //     bytes_rec = recvfrom(server_fd, buffer, 1024, 0, (struct sockaddr *)&cli_addr, &address_length);
    //     if (bytes_rec == -1) {
    //     	perror("read err");
    //     	exit(1);
    //     }
    //     printf("%s\n", buffer);
    // }

    // close(server_fd);
    // unlink(filename);

    return 0;
}