#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8080
#define BUFFER_SIZE 1024

// CRC32 hash function
unsigned long crc32(unsigned char *buf, size_t len) {
    unsigned long crc = 0xFFFFFFFF;
    for (size_t i = 0; i < len; i++) {
        crc ^= buf[i];
        for (size_t j = 8; j; j--) {
            crc = (crc & 1) ? (crc >> 1) ^ 0xEDB88320 : crc >> 1;
        }
    }
    return crc ^ 0xFFFFFFFF;
}

int main() {
    int server_fd, new_socket;
    struct sockaddr_in addr;
    socklen_t addr_len = sizeof(addr);
    char buffer[BUFFER_SIZE], hash[9]; // Ensure correct size for null termination

    // Set up the server address
    addr.sin_family = AF_INET;
    addr.sin_port = htons(PORT);
    addr.sin_addr.s_addr = INADDR_ANY;

    // Create socket
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        perror("Socket creation failed");
        return 1;
    }

    // Bind socket
    if (bind(server_fd, (struct sockaddr *)&addr, sizeof(addr)) == -1) {
        perror("Binding socket failed");
        close(server_fd);
        return 1;
    }

    // Listen for incoming connections
    if (listen(server_fd, 3) == -1) {
        perror("Listening failed");
        close(server_fd);
        return 1;
    }

    printf("Server listening on port %d...\n", PORT);

    while (1) {
        // Accept a connection
        new_socket = accept(server_fd, (struct sockaddr *)&addr, &addr_len);
        if (new_socket == -1) {
            perror("Accepting connection failed");
            continue;
        }

        // Receive data
        int bytes_received = recv(new_socket, buffer, BUFFER_SIZE - 1, 0); // Reserve space for null character
        if (bytes_received <= 0) {
            perror("Receiving data failed or connection closed by client");
            close(new_socket);
            continue;
        }

        buffer[bytes_received] = '\0'; // Null-terminate the string

        // Generate and send hash
        sprintf(hash, "%08lx", crc32((unsigned char *)buffer, bytes_received));
        if (send(new_socket, hash, strlen(hash), 0) == -1) {
            perror("Sending hash failed");
        }

        printf("Received: %s\nSent hash: %s\n", buffer, hash);
        close(new_socket);
    }

    close(server_fd);
    return 0;
}

