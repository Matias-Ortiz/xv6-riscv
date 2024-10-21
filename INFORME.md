# Tarea 1: Implementación de Llamadas al Sistema en xv6

## Objetivo
Implementar y modificar llamadas al sistema en xv6, un sistema operativo educativo.

## Parte I: Implementación Básica
### Nueva llamada al sistema: `int getppid(void)`
Se implementó la llamada al sistema `getppid()`, que retorna el ID del proceso padre del proceso que la invoca.

### Pasos realizados:
1. **Añadir prototipo en `sysproc.c`**:
   - Se agregó la función `int sys_getppid(void)` en `sysproc.c`, que utiliza la función `myproc()->parent->pid` para obtener el ID del proceso padre.
2. **Modificar archivos de llamadas al sistema**:
   - Se modificó `syscall.h` para agregar el identificador de la llamada.
   - Se actualizó `syscall.c` para incluir la función `sys_getppid()`.
3. **Modificar Makefile**:
   - Se editó el `Makefile` para compilar el nuevo programa de prueba, `yosoytupadre.c`.
4. **Crear el programa de prueba `yosoytupadre.c`**:
   - Se creó un programa que llama a `getppid()` y muestra el ID del proceso padre en la consola.

## Parte II: Implementación Avanzada
### Nueva llamada al sistema: `int getancestor(int)`
Se implementó la llamada al sistema `getancestor(int)`, que permite obtener el ancestro indicado en el parámetro:
- `getancestor(0)`: Retorna el mismo proceso.
- `getancestor(1)`: Retorna el proceso padre.
- `getancestor(2)`: Retorna el abuelo.
- Si el número indicado no es válido, retorna -1.

### Pasos realizados:
1. **Añadir prototipo en `sysproc.c`**:
   - Se agregó la función `int sys_getancestor(int n)` en `sysproc.c`, que itera sobre la lista de procesos ancestros hasta el nivel indicado.
2. **Modificar archivos de llamadas al sistema**:
   - Se modificó `syscall.h` para agregar el identificador de la llamada.
   - Se actualizó `syscall.c` para incluir la función `sys_getancestor()`.
3. **Crear un programa de prueba adicional**:
   - Se creó un programa llamado `ancestro.c` para verificar el funcionamiento de `getancestor(int)`.

## Dificultades encontradas y soluciones
- **Error al compilar**: Hubo problemas al compilar debido a una falta de declaración en `syscall.c` y `syscall.h`. Se solucionó al revisar la estructura de otras llamadas simples, como `getpid()`.
- **Problemas con GitHub**: Se encontró un archivo grande (`qemu-7.2.0.tar.xz`) que impedía el push a GitHub. Se utilizó Git LFS para manejar el archivo grande y poder subir la rama con éxito.
- **Error "undefined reference"**: Ocurrió al probar el programa de prueba. Se solucionó revisando la inclusión de headers en los archivos correspondientes.

## Conclusión
La implementación de las llamadas al sistema en xv6 permite entender cómo se estructuran y gestionan las funcionalidades del sistema operativo a nivel del kernel. Se realizaron dos nuevas llamadas al sistema y se probaron con programas específicos para validar su funcionamiento.


## Enlace a la rama en GitHub
[Enlace a la rama Tarea_1](https://github.com/Matias-Ortiz/xv6-riscv/tree/Tarea_1)
