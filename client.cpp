#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h> 
#include <arpa/inet.h>  
#include <unistd.h>  
#include <fstream>
#include <iostream>
#define MAX 80
#define PORT 8053
#define SA struct sockaddr
  
using namespace std;
  
int main()
{
    int sockfd, connfd;
    struct sockaddr_in servaddr, cli;
  
    // socket create and varification
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
    servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    servaddr.sin_port = htons(PORT);
  
    // connect the client socket to server socket
    if (connect(sockfd, (SA*)&servaddr, sizeof(servaddr)) != 0) {
        printf("connection with the server failed...\n");
        exit(0);
    }
    else
        printf("connected to the server..\n");
        
    ofstream writeLog;
    writeLog.open("logRecebido.txt");
    
	int contador = 0;    
	char buff[100] = {0};
	int n;
	int lenC;
	int found;
	cout << sizeof(buff) << endl;
    while((n = recv(sockfd, buff, sizeof(buff), 0)) > 0){
		for(int i = 0; i < n; i++){
			if(buff[i] == '/'){
				buff[i+1] = '\n';
			}
		}
		//buff[28] = '\n';
		cout << n << endl;
		printf("%d: _%s_\n",contador,buff);
    	writeLog << buff;
	   // memset(buff,'0',100);
		contador++;	
    }
    
    writeLog.close();
  
    close(sockfd);
    return 0;
}
