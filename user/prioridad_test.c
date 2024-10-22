#include "kernel/types.h"
#include "user/user.h"

int main() {
    for (int i = 0; i < 20; i++) {
        int pid = fork();
        if (pid == 0) {
            // Código del proceso hijo
            printf("Ejecutando proceso hijo %d\n", getpid());
            sleep(1);  // Añade una pausa para dar tiempo a imprimir
            exit(0);
        } else {
            // Proceso padre espera a que el hijo termine
            wait(0);
        }
    }

    exit(0);
}

