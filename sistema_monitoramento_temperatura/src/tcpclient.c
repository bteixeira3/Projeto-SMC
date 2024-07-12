// tcpclient.c
#include "tcpclient.h"

SOCKET connect_to_server(const char* server_ip, int port) {
    WSADATA wsa_data;
    SOCKET server_socket;
    struct sockaddr_in server_addr;

    WSAStartup(MAKEWORD(2, 2), &wsa_data);

    server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket == INVALID_SOCKET) {
        printf("Erro ao criar o socket.\n");
        exit(1);
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = inet_addr(server_ip);
    server_addr.sin_port = htons(port);

    if (connect(server_socket, (struct sockaddr*)&server_addr, sizeof(server_addr)) == SOCKET_ERROR) {
        printf("Erro ao conectar ao servidor.\n");
        closesocket(server_socket);
        exit(1);
    }

    return server_socket;
}



