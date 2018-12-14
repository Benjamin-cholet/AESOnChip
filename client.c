/*
	Dummy UDP client
*/

#include <stdio.h> 
#include <strings.h> 
#include <sys/types.h> 
#include <arpa/inet.h> 
#include <sys/socket.h> 
#include<netinet/in.h> 
#include<unistd.h> 
#include<stdlib.h> 

#define SERVER_ADDR "127.0.0.1"
#define PORT 5000 
#define BUFSIZE 1000

const uint8_t key_msg[17] = {'k', 0x2b, 0x7e, 0x15, 0x16, 0x28, 0xae, 0xd2, 0xa6, 0xab, 0xf7, 0x15, 0x88, 0x09, 0xcf, 0x4f, 0x3c};
const uint8_t p_msg[17] = {'p', 0x6b, 0xc1, 0xbe, 0xe2, 0x2e, 0x40, 0x9f, 0x96, 0xe9, 0x3d, 0x7e, 0x11, 0x73, 0x93, 0x17, 0x2a};
const uint8_t fast_msg[17] = {'f', 0x6b, 0xc1, 0xbe, 0xe2, 0x2e, 0x40, 0x9f, 0x96, 0xe9, 0x3d, 0x7e, 0x11, 0x73, 0x93, 0x17, 0x2a};
const uint8_t go_msg[1] = {'g'};
const uint8_t cipher_msg[1] = {'c'};
const uint8_t test_msg[1] = {'t'};

int main(int argc, char **argv) {

	uint8_t buf[BUFSIZE]; 
	int sockfd, n; 
	struct sockaddr_in servaddr; 

	// clear servaddr 
	memset(&servaddr, 0, sizeof(servaddr)); 
	servaddr.sin_addr.s_addr = inet_addr(SERVER_ADDR); 
	servaddr.sin_port = htons(PORT); 
	servaddr.sin_family = AF_INET; 

	// create datagram socket 
	sockfd = socket(AF_INET, SOCK_DGRAM, 0); 

	// connect to server 
	if(connect(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr)) < 0) {

		puts("\n Error : Connect Failed \n"); 
		exit(0); 
	}

	// request to send datagram 
	// no need to specify server address in sendto 
	// connect stores the peers IP and port

	switch (argv[1][0]) {

		case 'k':

			sendto(sockfd, key_msg, 17, 0, (struct sockaddr*)NULL, sizeof(servaddr)); 
			break;
		case 'p' :

			sendto(sockfd, p_msg, 17, 0, (struct sockaddr*)NULL, sizeof(servaddr)); 
			break;

		case 'f' :
			sendto(sockfd, fast_msg, 17, 0, (struct sockaddr*)NULL, sizeof(servaddr)); 
			break;
		case 'g' :

			sendto(sockfd, go_msg, 1, 0, (struct sockaddr*)NULL, sizeof(servaddr)); 
			break;
		case 'c' :

			sendto(sockfd, cipher_msg, 1, 0, (struct sockaddr*)NULL, sizeof(servaddr)); 
			break;
		case 't' :

			sendto(sockfd, test_msg, 1, 0, (struct sockaddr*)NULL, sizeof(servaddr)); 
			break;            
	}

	// waiting for response 
	recvfrom(sockfd, buf, sizeof(buf), 0, (struct sockaddr*)NULL, NULL); 
	puts((char *)buf); 

	// close the descriptor 
	close(sockfd); 
} 