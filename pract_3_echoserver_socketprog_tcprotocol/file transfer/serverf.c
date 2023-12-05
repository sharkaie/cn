#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8080

void error(const char *message) {
    perror(message);
    exit(1);
}

int main() {
    int server_socket, client_socket;
    struct sockaddr_in server_addr, client_addr;
    socklen_t client_len = sizeof(client_addr);
    FILE *file;
    char filename[256]; // Maximum filename length

    // Create socket
    server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket == -1) {
        error("Error in socket creation");
    }

    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    server_addr.sin_addr.s_addr = INADDR_ANY;

    // Bind socket
    if (bind(server_socket, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1) {
        error("Error in binding");
    }

    // Listen for incoming connections
    if (listen(server_socket, 5) == -1) {
        error("Error in listening");
    }

    printf("Server is listening on port %d...\n", PORT);

    // Accept connection from client
    client_socket = accept(server_socket, (struct sockaddr *)&client_addr, &client_len);
    if (client_socket == -1) {
        error("Error in accepting");
    }

    printf("Enter the filename to send: ");
    scanf("%s", filename);

    // Open the file to be sent
    file = fopen(filename, "rb");
    if (file == NULL) {
        error("Error opening file");
    }

    char buffer[1024];
    int n;
    
    // Read and send the file data to the client
    while ((n = fread(buffer, 1, sizeof(buffer), file)) > 0) {
        if (send(client_socket, buffer, n, 0) == -1) {
            error("Error in sending file");
        }
    }

    printf("File sent successfully.\n");

    // Close sockets and file
    fclose(file);
    close(client_socket);
    close(server_socket);

    return 0;
}