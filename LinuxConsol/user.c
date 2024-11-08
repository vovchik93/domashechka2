#include "user.h"
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

// Структура для хранения информации о пользователе
typedef struct {
    char* username;
    char* homedir;
} User;

// Сравнительная функция для сортировки пользователей по имени
int compare_users(const void* a, const void* b) {
    User* user_a = (User*)a;
    User* user_b = (User*)b;
    return strcmp(user_a->username, user_b->username);
}

// Функция для вывода списка пользователей и их домашних директорий
void print_users(void) {
    struct passwd* pw;
    User users[1024]; // Массив для хранения информации о пользователях
    int user_count = 0;

    // Перебираем записи в /etc/passwd
    while ((pw = getpwent()) != NULL) {
        users[user_count].username = strdup(pw->pw_name);
        users[user_count].homedir = strdup(pw->pw_dir);
        user_count++;
    }

    // Завершаем работу с /etc/passwd
    endpwent();

    // Сортируем пользователей по имени
    qsort(users, user_count, sizeof(User), compare_users);

    // Выводим список пользователей и их домашних директорий
    for (int i = 0; i < user_count; i++) {
        printf("%s\t%s\n", users[i].username, users[i].homedir);

        // Освобождаем память, выделенную для username и homedir
        free(users[i].username);
        free(users[i].homedir);
    }
}

