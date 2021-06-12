#ifndef EX3_SEND_RECV_TOOLS_H
#define EX3_SEND_RECV_TOOLS_H

#include <sys/types.h>
#include <sys/socket.h>
#include "buffer.h"



int ReceiveMsg(int socket, Buffer* BufferToReceive, int required_suffixes);
int SendMsg(int socket, Buffer* BufferToSend, int BytesToSend);

#endif  // EX3_SEND_RECV_TOOLS_H
