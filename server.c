/*
  encrypt.c
  20181203

  AESOnChip

  Benjamin Cholet
  Jean-Baptiste Valladeau
*/

#include <stdio.h> 
#include <strings.h> 
#include <sys/types.h> 
#include <arpa/inet.h> 
#include <sys/socket.h> 
#include <netinet/in.h>

#include "aes.h"

#define PORT 5000
#define BUFSIZE 1000

int main(void) {  

	uint8_t buf[BUFSIZE]; 
	int8_t ok_message[3] = {'o', 'k', '\0'};
	int8_t hello_message[6] = {'H', 'E', 'L', 'L', 'O', '\0'};
	int listenfd;
	socklen_t len; 
	struct sockaddr_in servaddr, cliaddr; 
	bzero(&servaddr, sizeof(servaddr)); 

	uint8_t key[16];
	uint8_t text[16];
	uint8_t cipher[16];
	struct AES_ctx ctx;

	// Create a UDP Socket 
	listenfd = socket(AF_INET, SOCK_DGRAM, 0);         
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY); 
	servaddr.sin_port = htons(PORT); 
	servaddr.sin_family = AF_INET;  

	// bind server address to socket descriptor 
	bind(listenfd, (struct sockaddr*)&servaddr, sizeof(servaddr)); 
		
	// send the response 

	while(1) {

		//receive the datagram
		memset(buf, 0, BUFSIZE);
		len = sizeof(cliaddr); 
		int n = recvfrom(listenfd, buf, sizeof(buf), 
				0, (struct sockaddr*)&cliaddr,&len); 
		
		switch(buf[0]) {

			case 'k' :

				memset(&ctx, 0, sizeof(ctx));
				AES_init_ctx(&ctx, buf+1);
				puts("A new key has been set up successfully.\n");
				break;
			case 'p' :

				puts("Received plain text");
				memcpy(text, buf+1, 16);

			case 'g' :

				puts("Received go command");
				memcpy(cipher, text, 16);

				AES_ECB_encrypt(&ctx, cipher);
				break;
			case 'c':

				puts("Received c command");
				sendto(listenfd, cipher, 16, 0, 
					(struct sockaddr*)&cliaddr, sizeof(cliaddr));

				break;
			case 'f' :

				puts("Received 'f' command.\n");
				memcpy(cipher, buf+1, 16);
				AES_ECB_encrypt(&ctx, cipher);

				for(int i = 0; i<16; i++)
					printf("%.2X", cipher[i]);
				printf("\n");
				break;
			case 't' :

				sendto(listenfd, ok_message, 3, 0, 
				(struct sockaddr*)&cliaddr, sizeof(cliaddr));
				break;
			default:

				break;
		}

		sendto(listenfd, hello_message, 6, 0, 
		(struct sockaddr*)&cliaddr, sizeof(cliaddr)); 
	}

	return 0;
}