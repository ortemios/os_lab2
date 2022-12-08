#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define BUFFER_SIZE 128

int main(int argc, char *argv[]) {
    int pid;
    int vendor_id, device_id;
    FILE *file = fopen("/sys/kernel/debug/lab/2", "r+");
    if (
        sscanf(argv[1], "%d", &pid) && 
        sscanf(argv[2], "%d", &vendor_id) && 
        sscanf(argv[3], "%d", &device_id) && 
        file
    ) {
        char *buffer[BUFFER_SIZE];
        fprintf(file, "pid: %d, vendor_id: %d, device_id: %d\n", pid, vendor_id, device_id);
        while (true) {
            char *result = fgets(buffer, BUFFER_SIZE, file);
            if (feof(file)) break;
            printf(result);
        }
    } else {
        printf("Usage: sudo ./user_program `pid` `vendor_id` `device_id`");
    }
    fclose(file);
    return 0;
}
