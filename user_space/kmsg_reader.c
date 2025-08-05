#include <stdio.h>    // For printf, fprintf, perror
#include <stdlib.h>   // For exit
#include <fcntl.h>    // For open
#include <unistd.h>   // For read, close

#define KMSG_PATH "/dev/kmsg"
#define BUFFER_SIZE 4096 // A reasonable buffer size for reading kernel messages

int main() {
    int fd;
    char buffer[BUFFER_SIZE];
    ssize_t bytes_read;

    printf("Attempting to open %s to read kernel messages...\n", KMSG_PATH);
    printf("Note: This program will block and print new kernel messages as they occur.\n");
    printf("      You may need root privileges (e.g., sudo) to run this.\n");
    printf("      Press Ctrl+C to stop.\n\n");

    // Open /dev/kmsg for reading
    fd = open(KMSG_PATH, O_RDONLY);
    if (fd == -1) {
        perror("Failed to open /dev/kmsg");
        fprintf(stderr, "Make sure you have appropriate permissions (e.g., run with sudo).\n");
        exit(EXIT_FAILURE);
    }

    printf("Successfully opened %s. Waiting for kernel messages...\n", KMSG_PATH);

    // Read and print messages continuously
    while (1) {
        bytes_read = read(fd, buffer, sizeof(buffer) - 1); // Leave space for null terminator
        if (bytes_read == -1) {
            perror("Error reading from /dev/kmsg");
            close(fd);
            exit(EXIT_FAILURE);
        }
        if (bytes_read > 0) {
            buffer[bytes_read] = '\0'; // Null-terminate the string
            printf("%s", buffer);     // Print the message
        }
    }

    // This part will not be reached in the infinite loop, but good practice
    close(fd);
    return 0;
}
