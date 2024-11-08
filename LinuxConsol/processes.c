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

// Структура для хранения информации о процессе
typedef struct {
    int pid;
} Process;

// Сравнительная функция для сортировки процессов по PID
int compare_processes(const void* a, const void* b) {
    Process* process_a = (Process*)a;
    Process* process_b = (Process*)b;
    return process_a->pid - process_b->pid;
}

// Функция для вывода списка запущенных процессов
void print_processes(void) {
    DIR* dp;
    struct dirent* dir;
    char path[MAX_PATH_LEN];
    Process processes[1024]; // Массив для хранения информации о процессах
    int process_count = 0;

    // Открываем директорию /proc
    dp = opendir("/proc");
    if (dp == NULL) {
        perror("opendir");
        exit(1);
    }

    // Перебираем записи в /proc
    while ((dir = readdir(dp)) != NULL) {
        // Пропускаем не числовые записи
        if (dir->d_name[0] < '0' || dir->d_name[0] > '9') {
            continue;
        }

        // Формируем путь к процессу
        snprintf(path, MAX_PATH_LEN, "/proc/%s/stat", dir->d_name);

        // Открываем файл статуса процесса
        FILE* fp = fopen(path, "r");
        if (fp == NULL) {
            continue;
        }

        // Считываем данные о статусе процесса
        char buffer[1024];
        fgets(buffer, 1024, fp);
        fclose(fp);

        // Разделяем данные о статусе процесса по пробелам
        char* token = strtok(buffer, " ");
        processes[process_count].pid = atoi(token);
        process_count++;
    }

    // Завершаем работу с директорией /proc
    closedir(dp);

    // Сортируем процессы по PID
    qsort(processes, process_count, sizeof(Process), compare_processes);

    // Выводим список процессов
    for (int i = 0; i < process_count; i++) {
        printf("%d\n", processes[i].pid);
    }
}
