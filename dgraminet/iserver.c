#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

int main() {
    struct sockaddr_in serv_addr, cli_addr;
    int server_fd, new_socket, valread;
    int portno = 9999;
    char buffer[1024];
    memset(buffer, 0, 1024);
    uint address_length;
    address_length = sizeof(serv_addr);

    if ((server_fd = socket(PF_INET, SOCK_DGRAM, 0)) == -1)// AF_INET or AF_UNIX
    {
        perror("error creating socket");
        exit(1);
    }

    serv_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    serv_addr.sin_port = htons(portno);
    serv_addr.sin_family = PF_INET;// AF_INET or AF_UNIX
    memset(serv_addr.sin_zero, '\0', sizeof serv_addr.sin_zero);

    if (bind(server_fd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) == -1) {
        perror("bind");
        exit(1);
        }
    while (1) {
        int bytes_rec = 0;
        bytes_rec = recvfrom(server_fd, buffer, 1024, 0, (struct sockaddr *)&cli_addr, &address_length);
        if (bytes_rec == -1) {
        	perror("read err");
        	exit(1);
        }
        printf("%s\n", buffer);
    }
    close(server_fd);

    return 0;
}