// echoserver.h
#ifndef ECHOSERVER_H
#define ECHOSERVER_H

#include "defs.h"
#include "tcpserver.h"

float sim_sensor(int sensor_id);
void handle_client(SOCKET client_socket, float temperatures[3]);
void update_temperatures(float temperatures[3]);

#endif // ECHOSERVER_H

