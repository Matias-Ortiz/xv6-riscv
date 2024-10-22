### Informe de Tarea 2: Programación de Procesos en xv6
# Objetivo
El objetivo de esta tarea fue modificar el programador de procesos en xv6 para implementar un sistema de prioridades y crear un programa de prueba llamado prioridad_test para demostrar su funcionalidad.

# Modificaciones Realizadas
1. Estructura de la Prioridad
Se agregó un campo de prioridad a la estructura del proceso en proc.h, junto con un campo de boost para gestionar el ajuste dinámico de la prioridad:


int priority; // Nivel de prioridad del proceso
int boost;    // Valor de ajuste de la prioridad
Estos campos se inicializaron en 0 para la prioridad y en 1 para el boost en la función allocproc en proc.c, garantizando que todos los nuevos procesos comiencen con la prioridad más alta.

2. Ajustes en el Scheduler
En el scheduler en proc.c, se implementó la lógica para ajustar la prioridad de los procesos. Por cada iteración en la cola de procesos, se incrementó la prioridad de los procesos ejecutables mediante el boost y se aplicaron reglas para cambiar la dirección del boost:

Si la prioridad alcanza 9, se establece boost = -1.
Si la prioridad llega a 0, se establece boost = 1.
3. Creación del Programa de Prueba
Se creó un programa llamado prioridad_test.c, que genera 20 procesos mediante la función fork(). Cada proceso imprime su PID y su ejecución se coordina usando wait() en el proceso padre para evitar problemas de colisiones de impresión en la consola.

# Problemas Encontrados y Soluciones
Problema 1: Error en el Makefile
Inicialmente, el Makefile no estaba configurado para compilar prioridad_test, lo que causaba un error al ejecutar make qemu. Esto se resolvió agregando $U/_prioridadtest al archivo UPROGS en el Makefile.

Problema 2: Impresión Desordenada
Al ejecutar prioridad_test, la salida de los procesos hijos era desordenada, lo cual hacía difícil verificar su funcionamiento. Esto se solucionó añadiendo wait() en el proceso padre, lo que permitió que los procesos se ejecutaran secuencialmente, asegurando una impresión más clara.

Problema 3: Error con found en el Scheduler
El código inicial del scheduler tenía un error con una variable found no utilizada. Se eliminó la declaración de la variable, ya que no era necesaria para la lógica de la tarea.

# Confirmación de Funcionamiento
Tras los cambios realizados, se confirmó que el sistema de prioridades y el programa de prueba funcionaron correctamente en xv6. La ejecución de prioridad_test mostró los procesos en orden de creación, sin desorden en la impresión.

# Conclusión
La tarea se completó exitosamente con la implementación de un sistema de prioridades en xv6 y la creación de un programa de prueba que demostró la funcionalidad requerida. Se presentaron varios desafíos, particularmente con la sincronización de la impresión en los procesos hijos, pero se resolvieron con ajustes en la lógica del código y el uso de funciones de control de procesos como wait().

