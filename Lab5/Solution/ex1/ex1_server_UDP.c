/* Sample UDP server */
#include <sys/socket.h>
#include <netinet/in.h>
#include <strings.h>
#include <stdio.h>

int main(int argc, char ** argv) {
	
	int sockfd, n;
	struct sockaddr_in servaddr, cliaddr;
	socklen_t len;
	char mesg[1000];
	char * banner = "Hello UDP client! This is UDP server";
	
	// Create a socket
	//socket is a number therefore it is int
	//AF_INET : Create a socket for ip addressing internet
	//SOCK_DGRAM : Transport Layer Protocol
	//0 specifies the socket protocol(default value is 0) 
	sockfd = socket(AF_INET, SOCK_DGRAM, 0);
	// Initialize server address
	servaddr.sin_family = AF_INET;						//sin_family specifies the family of the server
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);		//sin_addr.s_addr specifies to take the ip of the server automatically
	servaddr.sin_port = htons(32000);					//sin_port specifies the port of the server

	// Bind the socket
	// Bind the socket
	//first argument is the socket
	//second argument is the server
	//third argument is the size of the server
	bind(sockfd, (struct sockaddr * ) & servaddr, sizeof(servaddr));
	
	// Send and Receive
	len = sizeof(cliaddr);

	while(1){
		//receive from : getting the message from the client
		//n is the value of the recvfrom(if >0 then not successful)
		//first argument defines the socket
		//second argument defines the variable to receive the message
		//third argument defines the size of the message
		//fourth argument defines the 0 defaul value
		//fifth argument defiens the client 
		//sixth argument defines the size of the client
		n = recvfrom(sockfd, mesg, 1000, 0, (struct sockaddr * ) & cliaddr, & len);

		mesg[n] = 0;

		//printing the message from the client
		printf("Received: %s\n", mesg);

		//send some data to the client
		//first argument : socket
		//second argument : message to send
		//third argument : size of the message
		//fourth argument : 0 default value
		//fifth argument : client
		//size of the client
		sendto(sockfd, banner, n, 0, (struct sockaddr * ) & cliaddr, sizeof(cliaddr));
	}
	
	return 0;
}