#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8080
#define SERVER_IP "127.0.0.1"

void error(const char *message) {
    perror(message);
    exit(1);
}

int main() {
    int client_socket;
    struct sockaddr_in server_addr;
    FILE *file;
    char filename[256]; // Maximum filename length

    // Create socket
    client_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (client_socket == -1) {
        error("Error in socket creation");
    }

    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    server_addr.sin_addr.s_addr = inet_addr(SERVER_IP);

    // Connect to server
    if (connect(client_socket, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1) {
        error("Error in connection");
    }

    printf("Enter the filename to receive: ");
    scanf("%s", filename);

    // Open file for writing
    file = fopen(filename, "wb");
    if (file == NULL) {
        error("Error opening file");
    }

    char buffer[1024];
    int n;

    // Receive data from server and write to file
    while ((n = recv(client_socket, buffer, sizeof(buffer), 0)) > 0) {
        fwrite(buffer, 1, n, file);
    }

    printf("File received successfully.\n");

    // Close socket and file
    fclose(file);
    close(client_socket);

    return 0;
}