#include <stdio.h>
#include <stdlib.h>
#include "send_recv_tools.h"
#define TEMP_BUFFER_SIZE 1500



//the functions returns the message length
int ReceiveMsg(int socket, Buffer* BufferToReceive, int required_suffixes){
  int message_len=0;
  int recv_len=0;
  char temp_buffer[TEMP_BUFFER_SIZE];

  while (required_suffixes != BufferToReceive->suffixes) {
    recv_len = recv(socket, temp_buffer, TEMP_BUFFER_SIZE, 0);

    if (recv_len == -1 || recv_len ==0)  {
      fprintf(stderr, "-ERROR- recv() failed \n");
      exit(1);
    }

    append_to_buffer(BufferToReceive, temp_buffer, recv_len);

	//for debug:
	printf("-LB- recieved message:\n");
	print_buffer(BufferToReceive);
    message_len += recv_len;
  }
  return message_len;
}

int SendMsg(int socket, Buffer* BufferToSend, int BytesToSend) {

  const char* CurPlacePtr = BufferToSend->data;
  int BytesTransferred;
  int RemainingBytesToSend = BytesToSend;

  while (RemainingBytesToSend > 0)
  {

    BytesTransferred = send(socket, BufferToSend->data, BytesToSend, 0);
    if (BytesTransferred == -1)
    {
      fprintf(stderr, "-ERROR- send() failed\n");
      exit(1);
    }

    RemainingBytesToSend -= BytesTransferred;
    CurPlacePtr += BytesTransferred;
  }
  return 0;
}
