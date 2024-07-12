// messageclient.h
#ifndef MESSAGECLIENT_H
#define MESSAGECLIENT_H

#include "defs.h"
#include "tcpclient.h"

void motor_enable(bool status);
bool check_temperature(SOCKET server_socket, int sensor_id);
void update_temperatures(SOCKET server_socket);

#endif // MESSAGECLIENT_H


