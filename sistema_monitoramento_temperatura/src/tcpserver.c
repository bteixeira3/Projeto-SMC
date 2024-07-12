// tcpserver.c
#include "tcpserver.h"

SOCKET create_server_socket() {
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
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(PORT);

    if (bind(server_socket, (struct sockaddr*)&server_addr, sizeof(server_addr)) == SOCKET_ERROR) {
        printf("Erro ao vincular o socket.\n");
        closesocket(server_socket);
        exit(1);
    }

    listen(server_socket, 3);
    return server_socket;
}

SOCKET accept_client(SOCKET server_socket) {
    struct sockaddr_in client_addr;
    int client_addr_size = sizeof(client_addr);
    SOCKET client_socket = accept(server_socket, (struct sockaddr*)&client_addr, &client_addr_size);
    if (client_socket == INVALID_SOCKET) {
        printf("Erro ao aceitar conexão do cliente.\n");
    }
    return client_socket;
}

