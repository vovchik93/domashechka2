#include "logprint.h"


char* path_error = "error.txt";


void errors(const char* message) {
    FILE* fp = fopen(path_error, "a");
    if (fp == NULL) {
        perror("fopen");
        return;
    }

    fprintf(fp, "%s\n", message);
    fclose(fp);
}
