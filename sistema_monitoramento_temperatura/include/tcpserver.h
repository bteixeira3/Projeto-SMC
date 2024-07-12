// tcpserver.h
#ifndef TCPSERVER_H
#define TCPSERVER_H

#include "defs.h"

SOCKET create_server_socket();
SOCKET accept_client(SOCKET server_socket);

#endif // TCPSERVER_H
