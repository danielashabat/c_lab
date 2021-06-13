#ifndef SEND_RECV_TOOLS_H
#define SEND_RECV_TOOLS_H

#include "buffer.h"
#include <sys/socket.h>
#include <sys/types.h>

int ReceiveMsg(int socket, Buffer* BufferToReceive, int required_suffixes);
int SendMsg(int socket, Buffer* BufferToSend, int BytesToSend);

#endif
