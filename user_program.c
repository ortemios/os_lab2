#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define BUFFER_SIZE 128

int main(int argc, char *argv[]) {
    int pid;
    FILE *file = fopen("/sys/kernel/debug/lab/2", "r+");
    if (
        sscanf(argv[1], "%d", &pid) &&
        file
    ) {
        char *buffer[BUFFER_SIZE];
        printf("pid: %d\n", pid);
        while (true) {
            char *result = fgets(buffer, BUFFER_SIZE, file);
            if (feof(file)) break;
            printf(result);
        }
    } else {
        printf("Usage: sudo ./user_program `pid`");
    }
    fclose(file);
    return 0;
}
