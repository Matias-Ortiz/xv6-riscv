#include "kernel/types.h"
#include "user/user.h"

int main() {
    printf("Mi PID: %d\n", getpid());
    printf("PID de mi padre: %d\n", getppid());
    exit(0);
}
