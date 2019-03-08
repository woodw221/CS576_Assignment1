/*
 * I used pages 42-44 of the textbook, to help me write this as I found it while reading
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
#define max_pend 5

int main(){
	struct sockaddr_in sin;
	char buffer[max_len];
	int length;
	int x, new_x;
	

	// Build address data structure 
	bzero((char *)&sin, sizeof(sin));
	sin.sin_family = AF_INET;
	sin.sin_addr.s_addr = INADDR_ANY;
	sin.sin_port = htons(SERVER_PORT);

	// Setup Passive open 
	if ((x = socket (PF_INET, SOCK_STREAM, 0)) < 0){
		perror("Socket Error");
		exit(1);
	}

	if ((bind(x, (struct sockaddr *) &sin, sizeof(sin))) < 0){
		perror("Binding Error");
		exit(1);
	}
	listen(x, max_pend);

	//Listen for connection
	while(1){
		if ((new_x = accept(x, (struct sockaddr *)&sin, &length)) < 0){
			perror("Connection Error");
			exit(1);
		}
		while(length = recv(new_x, buffer, sizeof(buffer)-1, 0)){
			for(int i = 0; i < strlen(buffer); i++){
				
				buffer[i] = buffer[i] +1;
				
			}		
			printf("%s\n", buffer);
			send(new_x, buffer, length, 0);
			
		}
			
		close(new_x);
			
		
	}
}
