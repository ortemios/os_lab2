#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define BUFFER_SIZE 128

int main(int argc, char *argv[]) {
    int pid;
    char vfs_path[BUFFER_SIZE];
    FILE *file = fopen("/sys/kernel/debug/lab/2", "r+");
    if (
        sscanf(argv[1], "%d", &pid) && 
        sscanf(argv[2], "%s", vfs_path) && 
        file
    ) {
        char *buffer[BUFFER_SIZE];
        fprintf(file, "task_cputime (pid): %d, vfsmount (path): %s\n", pid, vfs_path);
        while (true) {
            char *result = fgets(buffer, BUFFER_SIZE, file);
            if (feof(file)) break;
            printf(result);
        }
    } else {
        printf("Usage: sudo ./user_program `pid` `path`");
    }
    fclose(file);
    return 0;
}
