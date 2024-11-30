#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/fs.h"
#include "kernel/fcntl.h"

void assert_result(int result, char *message) {
  if (result < 0) {
    printf("Falló: %s\n", message);
  } else {
    printf("Exitoso: %s\n", message);
  }
}

int main() {
  char *filename = "archivo_test.txt";
  int fd;

  // Crear archivo
  fd = open(filename, O_CREATE | O_RDWR);
  assert_result(fd, "Creación del archivo");

  // Escritura inicial
  assert_result(write(fd, "Prueba inicial", 14), "Escribir en archivo");
  close(fd);

  // Cambiar permisos a solo lectura
  assert_result(chmod(filename, 1), "Cambiar permisos a solo lectura");
  fd = open(filename, O_WRONLY);
  if (fd >= 0) {
    printf("Falló: Permiso de solo lectura no respetado.\n");
    close(fd);
  } else {
    printf("Exitoso: No se puede abrir en modo escritura.\n");
  }

  // Cambiar permisos a lectura/escritura
  assert_result(chmod(filename, 3), "Cambiar permisos a lectura/escritura");
  fd = open(filename, O_RDWR);
  assert_result(write(fd, "Prueba final", 12), "Escribir tras restaurar permisos");
  close(fd);

  // Cambiar permisos a inmutable
  assert_result(chmod(filename, 5), "Cambiar permisos a inmutable");
  fd = open(filename, O_WRONLY);
  if (fd >= 0) {
    printf("Falló: Archivo inmutable abierto para escritura.\n");
    close(fd);
  } else {
    printf("Exitoso: Archivo inmutable protegido correctamente.\n");
  }

  // Intentar cambiar permisos de inmutable
  int result = chmod(filename, 3);
  if (result == 0) {
    printf("Falló: Permisos de archivo inmutable fueron cambiados.\n");
  } else {
    printf("Exitoso: No se permitió cambiar permisos de archivo inmutable.\n");
  }

  printf("Todas las pruebas completadas.\n");
  exit(0);
}

