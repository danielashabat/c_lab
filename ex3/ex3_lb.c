#include "buffer.h"
#include "socket_tools.h"
#include <netdb.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#define NUM_SERVERS 3

// credit to: https://www.geeksforgeeks.org/tcp-server-client-implementation-in-c/
int main()
{
  int sock_server, con_http, len;
  int con_server[NUM_SERVERS];
  int i = 0;
  int sock_http;
  struct sockaddr_in server, http;
  Buffer buffer;
  int msg_len = 0;
  srand(time(0));
  sock_server = create_new_socket();
  bind_and_listen(sock_server, SERVER);
  sock_http = create_new_socket();
  bind_and_listen(sock_http, HTTP);
  len = sizeof(server);
  for (i = 0; i < NUM_SERVERS; i++) {
    con_server[i] = accept(sock_server, (struct sockaddr*)&server, &len);
    if (con_server[i] < 0) {
      printf("lb acccept failed...\n");
      exit(0);
    }
  }
  buffer.data = NULL;
  while (1) {
    for (i = 0; i < NUM_SERVERS; i++) {
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
  free_buffer(&buffer);
  return 0;
}
