#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>

int main() {
    int status;
    status = system("ls invalid_path");

    if (WIFEXITED(status)) {
        int exit_status = WEXITSTATUS(status);
        printf("Exit status: %d\n", exit_status);
    }

    return 0;
}
