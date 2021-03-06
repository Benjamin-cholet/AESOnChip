#include <stdio.h>
#include <unistd.h>
#include <netdb.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include "trigger.h"
#include "aes.h"
#define MAX 80
#define PORT 5000
#define BUFSIZE 80

#define SA struct sockaddr

uint8_t key[16];
uint8_t text[16];
uint8_t cipher[16];
struct AES_ctx ctx;

// Function designed for chat between client and server.
void func(int sockfd)
{
    uint8_t buf[MAX];
    int n;
    int8_t ok_message[3] = {'o', 'k', '\0'};
    int8_t hello_message[6] = {'H', 'E', 'L', 'L', 'O', '\0'};
    // infinite loop for chat
	
int i = 0;

    while(1) {

	struct timeval timeout;
	timeout.tv_sec = 2;
	timeout.tv_usec = 0;

	int rv;
	fd_set set;
	FD_ZERO(&set);
	FD_SET(sockfd, &set);
	rv = select(sockfd +1, &set, NULL, NULL, &timeout);

	if (rv < 0) {
		printf("error select\n"); 
		return;
}
	if (rv == 0) {
		printf("timeout\n");
		return;
}

        //receive the datagram
        memset(buf, 0, BUFSIZE);
        read(sockfd, buf, sizeof(buf));

	i=0;
	while (buf[i] != 0) {

		if (buf[i] == 0x0D) {
			i += 1;
			continue;
		}
		if (buf[i] == 0x0A) {
			i += 1;
			continue;
		}


//for (int j=0; j< sizeof(buf); j++) 
	//printf("%.2X ", buf[j]);


        switch(buf[i]) {

            case 'k' :

                memset(&ctx, 0, sizeof(ctx));
                AES_init_ctx(&ctx, buf+i+1);
                puts("A new key has been set up successfully.\n");
                i += 17;

		break;
            case 'p' :

                puts("Received plain text");
                memcpy(text, buf+i+1, 16);
		i += 17;
		break;
            case 'g' :

                puts("Received go command");
                memcpy(cipher, text, 16);
                AES_ECB_encrypt(&ctx, cipher);
                i += 1;
		break;
            case 'c':

                puts("Received c command");
                write(sockfd, cipher, 16);
                i += 1;
		break;
            case 'f' :

                puts("Received 'f' command.\n");
                memcpy(cipher, buf+i+1, 16);
                AES_ECB_encrypt(&ctx, cipher);
                write(sockfd, cipher, 16);
		i += 17;
                break;
            case 't' :
		puts("Received test cmd");
                write(sockfd, ok_message, 3);
 		i += 1;
               break;

            default:
		
                return;
        }





 	
	}
	


	}
   
}


// Driver function
int main()
{
trigger_init();

    int sockfd, connfd;
    int optval;
    socklen_t len;
    struct sockaddr_in servaddr, cli;

    // socket create and verification
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1) {
        printf("socket creation failed...\n");
        exit(0);
    }
    else
        printf("Socket successfully created..\n");
    bzero(&servaddr, sizeof(servaddr));

    // assign IP, PORT
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(PORT);

    optval = 1;
    setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR,
     (const void *)&optval, sizeof(int));

     // Binding newly created socket to given IP and verification
     if ((bind(sockfd, (SA*)&servaddr, sizeof(servaddr))) != 0) {
         printf("socket bind failed...\n");
         exit(0);
     }
     else
         printf("Socket successfully binded..\n");


    while (1) {

        // Now server is ready to listen and verification
        if ((listen(sockfd, 5)) != 0) {
            printf("Listen failed...\n");
            exit(0);
        }
        else
            printf("Server listening..\n");
        len = sizeof(cli);

        // Accept the data packet from client and verification
        connfd = accept(sockfd, (SA*)&cli, &len);
        if (connfd < 0) {
            printf("server acccept failed...\n");
            exit(0);
        }
        else
            printf("server acccept the client...\n");

        // Function for chatting between client and server
        func(connfd);
    }
}
