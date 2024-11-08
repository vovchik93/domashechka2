#include "processes.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <dirent.h>
#include <sys/stat.h>
#include <pwd.h>
#include <errno.h>

#define MAX_PATH_LEN 1024

// ��������� ��� �������� ���������� � ��������
typedef struct {
    int pid;
} Process;

// ������������� ������� ��� ���������� ��������� �� PID
int compare_processes(const void* a, const void* b) {
    Process* process_a = (Process*)a;
    Process* process_b = (Process*)b;
    return process_a->pid - process_b->pid;
}

// ������� ��� ������ ������ ���������� ���������
void print_processes(void) {
    DIR* dp;
    struct dirent* dir;
    char path[MAX_PATH_LEN];
    Process processes[1024]; // ������ ��� �������� ���������� � ���������
    int process_count = 0;

    // ��������� ���������� /proc
    dp = opendir("/proc");
    if (dp == NULL) {
        perror("opendir");
        exit(1);
    }

    // ���������� ������ � /proc
    while ((dir = readdir(dp)) != NULL) {
        // ���������� �� �������� ������
        if (dir->d_name[0] < '0' || dir->d_name[0] > '9') {
            continue;
        }

        // ��������� ���� � ��������
        snprintf(path, MAX_PATH_LEN, "/proc/%s/stat", dir->d_name);

        // ��������� ���� ������� ��������
        FILE* fp = fopen(path, "r");
        if (fp == NULL) {
            continue;
        }

        // ��������� ������ � ������� ��������
        char buffer[1024];
        fgets(buffer, 1024, fp);
        fclose(fp);

        // ��������� ������ � ������� �������� �� ��������
        char* token = strtok(buffer, " ");
        processes[process_count].pid = atoi(token);
        process_count++;
    }

    // ��������� ������ � ����������� /proc
    closedir(dp);

    // ��������� �������� �� PID
    qsort(processes, process_count, sizeof(Process), compare_processes);

    // ������� ������ ���������
    for (int i = 0; i < process_count; i++) {
        printf("%d\n", processes[i].pid);
    }
}
