#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>

void error(char* msg) {
	perror(msg);
	exit(0);
}

int main() {
	int sockfd;
	struct sockaddr_in serv_addr;
	char buffer[256];
	int portno = 9999;

	sockfd = socket(PF_INET, SOCK_DGRAM, 0); // PF_INET or PF_UNIX
	if (sockfd < 0)error("ERROR opening socket");

	serv_addr.sin_port = htons(portno);
	serv_addr.sin_family = PF_INET; // AF_INET or AF_UNIX
	serv_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
	memset(serv_addr.sin_zero, '\0', sizeof serv_addr.sin_zero);

	if (connect(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) error("ERROR connecting");

	strcpy(buffer,"Hello World\n");
	send(sockfd,buffer,13,0);

}