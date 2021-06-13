#include "buffer.h"
#include "send_recv_tools.h"
#include <netdb.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <time.h>
#include <unistd.h>


#define UPPER_PORT_LIMIT 63999
#define LOWER_PORT_LIMIT 1023
#define FILE_NAME 15
#define NUM_SERVERS 3

enum SOCKET_TYPES { SERVER, HTTP };
int create_new_socket();
int generate_random_port();
void write_port_to_file(int port, int socket_type);
void bind_and_listen(int sockfd, int socket_type);

// credit to: https://www.geeksforgeeks.org/tcp-server-client-implementation-in-c/
int main()
{
  int sock_server, con_http, len;
  int con_server[NUM_SERVERS];
  int i = 0;
  int sock_http;
  struct sockaddr_in cli, http;
  Buffer buffer;
  int msg_len = 0;
  srand(time(0));
  sock_server = create_new_socket();
  bind_and_listen(sock_server, SERVER);
  sock_http = create_new_socket();
  bind_and_listen(sock_http, HTTP);
  len = sizeof(cli);
  for (i = 0; i < NUM_SERVERS; i++) {
    con_server[i] = accept(sock_server, (struct sockaddr*)&cli, &len);
    if (con_server[i] < 0) {
      printf("lb acccept failed...\n");
      exit(0);
    }
 }
  buffer.data = NULL;
  while (1) {
    for(i=0;i<NUM_SERVERS;i++) {
      con_http = accept(sock_http, (struct sockaddr*)&http, &len);
      if (con_http < 0) {
        printf("lb acccept failed...\n");
        exit(0);
      }
      initialize_buffer(&buffer);
      msg_len = ReceiveMsg(con_http, &buffer, 1);
      SendMsg(con_server[i], &buffer, msg_len);
      initialize_buffer(&buffer);
      msg_len = ReceiveMsg(con_server[i], &buffer, 2);
      SendMsg(con_http, &buffer, msg_len);
      close(con_http);
    }
  }
  for (i = 0; i < NUM_SERVERS; i++) {
    close(con_server[i]);
  }
  close(sock_server);
  close(sock_http);
  free(&buffer);
  return 0;
}

int generate_random_port() { return (rand() % (UPPER_PORT_LIMIT - LOWER_PORT_LIMIT + 1)) + LOWER_PORT_LIMIT; }

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
    port = generate_random_port();
    printf("generate new port number...\n");
    printf("port number is: %d\n", port);
    write_port_to_file(port, socket_type);
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(port);
  } while ((bind(sockfd, (SA*)&servaddr, sizeof(servaddr))) != 0);

  printf("Socket successfully binded..\n");

  if ((listen(sockfd, 1)) != 0) {
    printf("Listen failed...\n");
    exit(0);
  } else{
    printf("lb listening..\n");
  }
}
