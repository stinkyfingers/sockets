#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <sys/un.h>
#include <unistd.h>



char *socket_path = "/tmp/test.sock";

int main() {
	struct sockaddr_un serv_addr;
    char buf[100];
    int server_fd, cl, rc;

    if ((server_fd = socket(AF_LOCAL, SOCK_STREAM, 0)) < 0) {
        perror("error creating socket"); 
        exit(1);
    }

    memset(&serv_addr, 0, sizeof(serv_addr));
	strncpy(serv_addr.sun_path, socket_path, sizeof(serv_addr.sun_path));
    serv_addr.sun_family = AF_LOCAL;

	if (connect(server_fd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
		perror("ERROR connecting"); exit(1);
	}

	while((rc=read(STDIN_FILENO, buf, sizeof(buf))) > 0) {
	    if (write(server_fd, buf, rc) != rc) {
	    	if (rc > 0) fprintf(stderr,"partial write");
		    else {
		        perror("write error");
		        exit(-1);
		    }
	    }
	}
    return 0;
}