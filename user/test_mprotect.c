#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int main() {
  char *addr = sbrk(0);  // Obtener la dirección actual del heap
  sbrk(4096);  // Añadir una página al heap

  // Paso 1: Proteger la página
  if (mprotect(addr, 1) == -1) {
    printf("mprotect falló\n");
    exit(1);
  }

  printf("mprotect: protección aplicada con éxito en addr: %p, len: 1\n", addr);

  // Paso 3: Desproteger la página
  if (munprotect(addr, 1) == -1) {
    printf("munprotect falló\n");
    exit(1);
  }
  
  printf("Escribiendo en la página desprotegida...\n");

  // Paso 4: Escribir un valor en la dirección para verificar si se puede escribir
  *addr = 'B';  // Esto debería funcionar si la desprotección es exitosa
  
  // Imprimir el valor almacenado en la dirección en formato ASCII y hexadecimal
  printf("Valor almacenado en la dirección (como ASCII): %c\n", *addr);
  printf("Valor almacenado en la dirección (como hexadecimal): 0x%x\n", *addr);

  return 0;
}

