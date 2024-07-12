// tcpclient.h
#ifndef TCPCLIENT_H
#define TCPCLIENT_H

#include "defs.h"

SOCKET connect_to_server(const char* server_ip, int port);

#endif // TCPCLIENT_H
