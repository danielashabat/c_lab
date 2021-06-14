#include "socket_tools.h"
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>

#define TEMP_BUFFER_SIZE 1500
#define UPPER_PORT_LIMIT 63999
#define LOWER_PORT_LIMIT 1023
#define FILE_NAME 15

int generate_random_port();
void write_port_to_file(int port, int socket_type);

// the functions returns the message length
int ReceiveMsg(int socket, Buffer* BufferToReceive, int required_suffixes)
{
  int message_len = 0;
  int recv_len = 0;
  char temp_buffer[TEMP_BUFFER_SIZE];

  while (required_suffixes != BufferToReceive->suffixes) {
    recv_len = recv(socket, temp_buffer, TEMP_BUFFER_SIZE, 0);

    if (recv_len == -1 || recv_len == 0) {
      fprintf(stderr, "-ERROR- recv() failed \n");
      exit(1);
    }

    append_to_buffer(BufferToReceive, temp_buffer, recv_len);

    message_len += recv_len;
  }
  return message_len;
}

int SendMsg(int socket, Buffer* BufferToSend, int BytesToSend)
{

  const char* CurPlacePtr = BufferToSend->data;
  int BytesTransferred;
  int RemainingBytesToSend = BytesToSend;

  while (RemainingBytesToSend > 0) {

    BytesTransferred = send(socket, BufferToSend->data, BytesToSend, 0);
    if (BytesTransferred == -1) {
      fprintf(stderr, "-ERROR- send() failed\n");
      exit(1);
    }

    RemainingBytesToSend -= BytesTransferred;
    CurPlacePtr += BytesTransferred;
  }
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
  }
  return sock;
}

void bind_and_listen(int sock, int socket_type)
{
  struct sockaddr_in servaddr;
  int port;
  bzero(&servaddr, sizeof(servaddr));

  do {
    port = generate_random_port();
    write_port_to_file(port, socket_type);
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(port);
  } while ((bind(sock, (struct sockaddr*)&servaddr, sizeof(servaddr))) != 0);

  if ((listen(sock, 1)) != 0) {
    printf("Listen failed...\n");
    exit(0);
  }
}
