// echoserver.c
#include "echoserver.h"

float sim_sensor(int sensor_id) {
    return 10.0 + (rand() / (float)RAND_MAX) * (84.5 - 10.0);
}

void handle_client(SOCKET client_socket, float temperatures[3]) {
    char buffer[BUFFER_SIZE];
    int bytes_received;

    while ((bytes_received = recv(client_socket, buffer, BUFFER_SIZE, 0)) > 0) {
        buffer[bytes_received] = '\0';
        char command[BUFFER_SIZE];
        char sensor_id_str[BUFFER_SIZE];
        int sensor_id;
        sscanf(buffer, "%s %s", command, sensor_id_str);

        if (strcmp(command, "gettemp") == 0) {
            if (strcmp(sensor_id_str, "T1") == 0) sensor_id = 1;
            else if (strcmp(sensor_id_str, "T2") == 0) sensor_id = 2;
            else if (strcmp(sensor_id_str, "T3") == 0) sensor_id = 3;
            else sensor_id = 0;

            if (sensor_id >= 1 && sensor_id <= 3) {
                sprintf(buffer, "Sensor %d: %.2f Celsius", sensor_id, temperatures[sensor_id - 1]);
            } else {
                sprintf(buffer, "ID do sensor inválido.");
            }
        } else if (strcmp(command, "update") == 0) {
            for (int i = 0; i < 3; i++) {
                temperatures[i] = sim_sensor(i + 1);
            }
            sprintf(buffer, "Temperaturas atualizadas.");
        } else {
            sprintf(buffer, "Comando não reconhecido.");
        }
        send(client_socket, buffer, strlen(buffer), 0);
    }
    closesocket(client_socket);
}

int main() {
    srand(time(NULL));
    SOCKET server_socket = create_server_socket();
    float temperatures[3] = {sim_sensor(1), sim_sensor(2), sim_sensor(3)};

    printf("Aguardando conexões na porta %d...\n", PORT);

    while (1) {
        SOCKET client_socket = accept_client(server_socket);
        handle_client(client_socket, temperatures);
    }

    closesocket(server_socket);
    WSACleanup();
    return 0;
}









