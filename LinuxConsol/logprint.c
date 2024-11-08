#include "logprint.h"


char* path = "log.txt";


void logprint(const char* message) {
    FILE* fp = fopen(path, "a");
    if (fp == NULL) {
        perror("fopen");
        return;
    }

    fprintf(fp, "%s\n", message);
    fclose(fp);
}
