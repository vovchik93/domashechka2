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

// ��������� ��� �������� ���������� � ������������
typedef struct {
    char* username;
    char* homedir;
} User;

// ������������� ������� ��� ���������� ������������� �� �����
int compare_users(const void* a, const void* b) {
    User* user_a = (User*)a;
    User* user_b = (User*)b;
    return strcmp(user_a->username, user_b->username);
}

// ������� ��� ������ ������ ������������� � �� �������� ����������
void print_users(void) {
    struct passwd* pw;
    User users[1024]; // ������ ��� �������� ���������� � �������������
    int user_count = 0;

    // ���������� ������ � /etc/passwd
    while ((pw = getpwent()) != NULL) {
        users[user_count].username = strdup(pw->pw_name);
        users[user_count].homedir = strdup(pw->pw_dir);
        user_count++;
    }

    // ��������� ������ � /etc/passwd
    endpwent();

    // ��������� ������������� �� �����
    qsort(users, user_count, sizeof(User), compare_users);

    // ������� ������ ������������� � �� �������� ����������
    for (int i = 0; i < user_count; i++) {
        printf("%s\t%s\n", users[i].username, users[i].homedir);

        // ����������� ������, ���������� ��� username � homedir
        free(users[i].username);
        free(users[i].homedir);
    }
}

