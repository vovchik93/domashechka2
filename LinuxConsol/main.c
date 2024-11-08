
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h> // הכÿ נאבמעû ס פאיכאלט 
#include <unistd.h> // הכÿ close() 
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "help.h"
#include "processes.h"
#include "errors.h"
#include "logprint.h"
#include "user.h"


int main(int argc, char* argv[]) {



    if (strcmp(argv[1], "-h") == 0 || strcmp(argv[1], "--help") == 0)helpPrint();

    if(strcmp(argv[1], "-p") == 0 || strcmp(argv[1], "--processes") == 0)print_processes();

    if (strcmp(argv[1], "-u") == 0 || strcmp(argv[1], "--users") == 0)print_users();

    if (strcmp(argv[1], "-l") == 0 || strcmp(argv[1], "-log") == 0) {
        path = argv[2];
        logprint("start log file");
    }

    if (strcmp(argv[1], "-e") == 0 || strcmp(argv[1], "-eror") == 0){
        path_error = argv[2];
        errors("start error file");
    }

    return 0;
}
