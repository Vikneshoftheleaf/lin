#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define SERVER_IP "127.0.0.1"
#define SERVER_PORT 8080
#define BUFFER_SIZE 1024

int main() {
    int sock;
    struct sockaddr_in server_addr;
    char buffer[BUFFER_SIZE], response[BUFFER_SIZE];

    // Set up server address
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(SERVER_PORT);
    server_addr.sin_addr.s_addr = inet_addr(SERVER_IP);

    // Create socket
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        perror("Socket creation failed");
        return 1;
    }

    // Connect to server
    if (connect(sock, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1) {
        perror("Connection failed");
        close(sock);
        return 1;
    }

    printf("Connected to server. Type 'exit' to quit.\n");

    while (1) {
        printf("Enter a string: ");
        if (!fgets(buffer, BUFFER_SIZE, stdin)) {
            perror("Error reading input");
            break;
        }

        // Check if user wants to exit
        if (strcmp(buffer, "exit\n") == 0) {
            break;
        }

        buffer[strcspn(buffer, "\n")] = '\0'; // Remove newline character from input

        // Send message to server
        if (send(sock, buffer, strlen(buffer), 0) == -1) {
            perror("Failed to send message");
            break;
        }

        // Receive response from server
        int bytes_received = recv(sock, response, BUFFER_SIZE - 1, 0); // Reserve space for null character
        if (bytes_received > 0) {
            response[bytes_received] = '\0'; // Null-terminate the response
            printf("Hashed response: %s\n", response);
        } else {
            perror("Failed to receive response or connection closed by server");
            break;
        }
    }

    close(sock); // Close socket
    printf("Connection closed.\n");
    return 0;
}

