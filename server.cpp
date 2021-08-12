#include <stdio.h>
#include <string.h>   
#include <sys/socket.h> 
#include <arpa/inet.h>  
#include <unistd.h>  
#include <iostream>
#include <string>
#include <fstream>   

using namespace std;

int main(void) {
  struct sockaddr_in server, client;
  int socket_fd, client_fd;

  socket_fd = socket(AF_INET, SOCK_STREAM, 0);
  if(socket_fd == -1){
    printf("Impossível criar socket\n");
  }

  server.sin_family = AF_INET;
  server.sin_addr.s_addr = INADDR_ANY;
  server.sin_port = htons(8053);

  if( bind(socket_fd,(struct sockaddr *)&server , sizeof(server)) < 0)
    {
        perror("Erro ao fazer bind");
        return 1;
    }
  puts("Bind feito com sucesso!\n");

  listen(socket_fd, 1);

  int c = sizeof(struct sockaddr_in);

  client_fd = accept(socket_fd, (struct sockaddr *)&client, (socklen_t*)&c);

  if(client_fd < 0){
    perror("Falha ao aceitar conexão!");
    return 1;
  }
  puts("Conexão realizada com sucesso!\n");
  
  ifstream ReadLog;
  
  ReadLog.open("log.txt");
  string linha;
  char Mensagem[100];
  
  if(ReadLog.is_open()){
  	while(getline(ReadLog, linha)){
  	   // write(client_fd, linha.c_str(), linha.size());
  		send(client_fd, linha.c_str(), linha.size(),0);
  		cout << linha << endl;
		
  	}
  }
  
  printf("Teste\n");
  
  ReadLog.close();

  close(client_fd);
  close(socket_fd);

  return 0;
}
