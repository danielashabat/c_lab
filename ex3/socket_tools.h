#ifndef SOCKET_TOOLS_H
#define SOCKET_TOOLS_H

#include "buffer.h"

enum SOCKET_TYPES { SERVER, HTTP };

int ReceiveMsg(int socket, Buffer* BufferToReceive, int required_suffixes);
int SendMsg(int socket, Buffer* BufferToSend, int BytesToSend);
void bind_and_listen(int sock, int socket_type);
int create_new_socket();

#endif
