#include "help.h"

void helpPrint(){
    printf("Usage:\n");
    printf("  -u, --users\tPrint a list of users and their home directories\n");
    printf("  -p, --processes\tPrint a list of running processes\n");
    printf("  -h, --help\tPrint this help message\n");
    printf("  -l PATH, --log PATH\tRedirect output to a file at the specified path\n");
    printf("  -e PATH, --errors PATH\tRedirect error output to a file at the specified path\n");
}
