// messageclient.c
#include "messageclient.h"

void motor_enable(bool status) {
    if (status) {
        printf("Motor acionado.\n");
    } else {
        printf("Motor desativado.\n");
    }
}

bool check_temperature(SOCKET server_socket, int sensor_id) {
    char buffer[BUFFER_SIZE];
    bool motor_status = false;

    // Envia uma solicitação para o sensor especificado
    sprintf(buffer, "gettemp T%d", sensor_id);
    send(server_socket, buffer, strlen(buffer), 0);

    // Recebe a resposta do servidor
    int bytes_received = recv(server_socket, buffer, BUFFER_SIZE, 0);
    buffer[bytes_received] = '\0';

    // Exibe a resposta recebida
    printf("%s\n", buffer);

    // Analisa a resposta e verifica a temperatura
    float temperature;
    sscanf(buffer, "Sensor %*d: %f Celsius", &temperature);
    if (temperature > 50.0) {
        motor_status = true;
    }

    return motor_status;
}

void update_temperatures(SOCKET server_socket) {
    char buffer[BUFFER_SIZE];
    // Envia uma solicitação ao servidor para atualizar as temperaturas
    sprintf(buffer, "update");
    send(server_socket, buffer, strlen(buffer), 0);

    // Recebe a confirmação do servidor
    int bytes_received = recv(server_socket, buffer, BUFFER_SIZE, 0);
    buffer[bytes_received] = '\0';
    printf("%s\n", buffer);
}

int main() {
    SOCKET server_socket = connect_to_server("127.0.0.1", PORT);
    char sensor_input[BUFFER_SIZE];
    bool motor_status[3] = {false, false, false};
    bool sensors_requested[3] = {false, false, false};
    int sensor_count = 0;

    while (1) { // Loop infinito para obter temperaturas continuamente
        printf("Digite o ID do sensor para solicitar a temperatura (T1, T2, T3) ou 'exit' para sair: ");
        scanf("%s", sensor_input);

        if (strcmp(sensor_input, "exit") == 0) {
            break;
        } else if (strcmp(sensor_input, "T1") == 0) {
            if (!sensors_requested[0]) {
                motor_status[0] = check_temperature(server_socket, 1);
                sensors_requested[0] = true;
                sensor_count++;
            } else {
                printf("Temperatura de T1 já solicitada nesta rodada. Solicite outro sensor.\n");
                continue;
            }
        } else if (strcmp(sensor_input, "T2") == 0) {
            if (!sensors_requested[1]) {
                motor_status[1] = check_temperature(server_socket, 2);
                sensors_requested[1] = true;
                sensor_count++;
            } else {
                printf("Temperatura de T2 já solicitada nesta rodada. Solicite outro sensor.\n");
                continue;
            }
        } else if (strcmp(sensor_input, "T3") == 0) {
            if (!sensors_requested[2]) {
                motor_status[2] = check_temperature(server_socket, 3);
                sensors_requested[2] = true;
                sensor_count++;
            } else {
                printf("Temperatura de T3 já solicitada nesta rodada. Solicite outro sensor.\n");
                continue;
            }
        } else {
            printf("ID do sensor inválido. Tente novamente.\n");
            continue;
        }

        if (sensor_count == 3) {
            // Verifica o status do motor após as três leituras
            bool final_motor_status = motor_status[0] || motor_status[1] || motor_status[2];
            motor_enable(final_motor_status);

            // Atualiza as temperaturas para a próxima rodada de verificações
            update_temperatures(server_socket);

            // Reinicia os estados das temperaturas para a próxima rodada de verificações
            motor_status[0] = motor_status[1] = motor_status[2] = false;
            sensors_requested[0] = sensors_requested[1] = sensors_requested[2] = false;
            sensor_count = 0;
        }
    }

    closesocket(server_socket);
    WSACleanup();
    return 0;
}

