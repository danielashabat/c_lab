#include <netdb.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include<time.h>
#include <unistd.h>
#include <assert.h>
#include "buffer.h"
#include "send_recv_tools.h"


#define SA struct sockaddr

#define UPPER_PORT_LIMIT 63999
#define LOWER_PORT_LIMIT 1023
#define FILE_NAME 15

enum SOCKET_TYPES { SERVER, HTTP };
int create_new_socket();
int generate_random_port();
void write_port_to_file(int port, int socket_type);
void bind_and_listen(int sockfd, int socket_type);

// credit to: https://www.geeksforgeeks.org/tcp-server-client-implementation-in-c/
int main()
{
  int sock_server, connfd, len;
  int sock_http;
  struct sockaddr_in cli;

  srand(time(0));
  // socket create and verification
  sock_server = create_new_socket();
  bind_and_listen(sock_server, SERVER);

  // create http socket
  sock_http = create_new_socket();
  bind_and_listen(sock_http, HTTP);

  len = sizeof(cli);

  // Accept the data packet from client and verification
  connfd = accept(sock_server, (SA*)&cli, &len);
  if (connfd < 0) {
    printf("server acccept failed...\n");
    exit(0);
  } else
    printf("server acccept the client...\n");

  // insert Functions here:
  Buffer buffer;
  buffer.data=NULL;
  initialize_buffer(&buffer);

  //receive message from HTTP until 1 suffixes
  char test_msg[49]="Accept-Language: en-US,en;q=0.8,he;q=0.6\\r\\n\\r\\n";
  append_to_buffer(&buffer,test_msg,49);
  print_buffer(&buffer);
  printf("num of suffix: %d\n",buffer.suffixes);
//  assert(buffer.suffixes==1);

  //send message to server
  SendMsg(connfd,&buffer, 49);

  //receive message from server until 2 suffixes
	initialize_buffer(&buffer);
	ReceiveMsg(connfd,&buffer, 2);
  //wait for another message from HTTP...

  //close the socket
  close(sock_server);
  close(sock_http);
	return 0;
}

int generate_random_port() {

  return (rand() % (UPPER_PORT_LIMIT - LOWER_PORT_LIMIT + 1)) + LOWER_PORT_LIMIT;
}

void write_port_to_file(int port, int socket_type)
{
  char file_name[FILE_NAME];
  if (socket_type == SERVER) {
    strcpy(file_name, "server_port");
  } else {
    strcpy(file_name, "http_port");
  }

  FILE* file = fopen(file_name, "w");
  fprintf(file, "%d", port);
  fclose(file);
}

int create_new_socket()
{
  int sock = socket(AF_INET, SOCK_STREAM, 0);
  if (sock == -1) {
    printf("socket creation failed...\n");
    exit(0);
  } else {
    printf("Socket successfully created..\n");
  }
  return sock;
}

void bind_and_listen(int sockfd, int socket_type)
{
  struct sockaddr_in servaddr;
  int port;
  bzero(&servaddr, sizeof(servaddr));

  do {
    // generate random number in range:  1024<port< 64000
    port = generate_random_port();
    printf("generate new port number...\n");
    printf("port number is: %d\n", port);
    write_port_to_file(port, socket_type);
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(port);
  } while ((bind(sockfd, (SA*)&servaddr, sizeof(servaddr))) != 0);

  printf("Socket successfully binded..\n");

  // Now server is ready to listen and verification
  if ((listen(sockfd, 5)) != 0) {
    printf("Listen failed...\n");
    exit(0);
  } else
    printf("Server listening..\n");
}
