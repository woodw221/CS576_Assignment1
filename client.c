/*
 * I used pages 41/42 of the text book, to help me write this as I found it while reading
 * and the code there really helped me understand the client and server
 */ 
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <strings.h>
#include <string.h>
#include <unistd.h>

#define SERVER_PORT 4565
#define max_len 256

int main (int argc, char * argv[]){
	FILE *fp;
	struct hostent *hp;
	struct sockaddr_in sin;
	char *host;
	char buffer[max_len];
	int x;
	int length;

	if(argc==2){
		host = argv[1];
	}
	
	else{
		fprintf(stderr, "Need hostname to connect\n");
		exit(1);
	}

	hp = gethostbyname(host);
	if(!hp){
		fprintf(stderr, "Unknown Host\n");
		exit(1);
	}
	//Build Structure to hold Address
	bzero((char *)&sin, sizeof(sin));
	sin.sin_family = AF_INET;
	bcopy(hp->h_addr, (char *)&sin.sin_addr, hp->h_length);
	sin.sin_port = htons(SERVER_PORT);
	//Attempt to Connect
	if ((x = socket(PF_INET, SOCK_STREAM, 0)) < 0){
		perror("Socket error");
		exit(1);
	}

	if(connect(x, (struct sockaddr *)&sin, sizeof(sin)) <0){
		perror("Connection Issue");
		close(x);
		exit(1);
	}
	// Send and Recieve Text
	while(fgets(buffer, sizeof(buffer), stdin)){
		buffer[max_len-1] = '\0';
		length = strlen(buffer) + 1;
		send(x, buffer, length, 0);

		length = recv(x, buffer, sizeof(buffer), 0);
		printf("%s\n", buffer);
	}
}
