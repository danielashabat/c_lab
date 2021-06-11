#include <sys/types.h>
#include <sys/socket.h>
#include "buffer.h"

#include TEMP_BUFFER_SIZE 1500



//the functions returns the message length
int ReceiveMsg(SOCKET socket, Buffer* BufferToReceive, int required_suffixes){
  int message_len=0;
  int recv_len=0;
  char temp_buffer[TEMP_BUFFER_SIZE];

  while (required_suffixes != BufferToReceive->suffixes) {
    recv_len = recv(socket, temp_buffer, TEMP_BUFFER_SIZE, 0);

    if (recv_len == SOCKET_ERROR) {
      fprintf(stderr, "-ERROR- recv() failed with error %d\n");
      exit(1);
    }

    append_to_buffer(Buffer * BufferToReceive, char* temp_buffer, int recv_len);
    message_len += recv_len;
  }
  return message_len;
}

int SendMsg(SOCKET socket, Buffer* BufferToSend, int BytesToSend) {

  const char* CurPlacePtr = BufferToSend->data;
  int BytesTransferred;
  int RemainingBytesToSend = BytesToSend;

  while (RemainingBytesToSend > 0)
  {

    BytesTransferred = send(socket, BufferToSend->data, BytesToSend, 0);
    if (BytesTransferred == SOCKET_ERROR)
    {
      fprintf(stderr, "-ERROR- sendto() failed, error %d\n");
      exit(1);
    }

    RemainingBytesToSend -= BytesTransferred;
    CurPlacePtr += BytesTransferred;
  }
  return 0;
}