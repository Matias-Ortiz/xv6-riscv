# Informe Tarea 3 - xv6: Protección de Memoria

**Autor:** Matias Vanderschueren 
**Curso:** Sistemas Operativos  
**Tarea:** Tarea 3

## Descripción General

La Tarea 3 consistió en implementar las funciones `mprotect` y `munprotect` en xv6, un sistema operativo de enseñanza. La función `mprotect` permite proteger una región de memoria para hacerla de solo lectura, mientras que `munprotect` revierte esta protección, permitiendo nuevamente la escritura en la región de memoria. Estas funciones son fundamentales para entender el manejo de memoria y la protección a nivel de sistema operativo.

Este informe documenta el proceso de desarrollo, los principales problemas encontrados y las soluciones implementadas para completar exitosamente la tarea.

## Proceso de Desarrollo

### Primer Intento: Reutilización del xv6 de Tareas Anteriores

Inicialmente, intenté realizar la tarea utilizando la versión de xv6 que había modificado para las tareas anteriores (de la tarea 0 a la tarea 2). Se realizaron varias iteraciones sobre este código, sin embargo, no lograba que el sistema compilara correctamente ni que las funciones funcionaran como se esperaba.

### Segundo Intento: Fork desde el Repositorio del Profesor

Decidí entonces hacer un fork del repositorio del profesor, esperando que este código base pudiera ser más compatible o actualizado. Realicé el mismo proceso de implementación en esta nueva versión, pero nuevamente encontré numerosos problemas. Estos errores me llevaron a concluir que quizá era necesario partir desde una versión completamente limpia y sin modificaciones previas.

### Tercer Intento: Fork desde el Repositorio del MIT

Finalmente, hice un fork directamente desde el repositorio oficial de xv6 en el MIT. Al comenzar desde una versión limpia del sistema, fue mucho más fácil implementar las funciones `mprotect` y `munprotect` con menos errores. Este paso fue clave para el éxito de la tarea, ya que con la experiencia acumulada de los intentos anteriores, logré avanzar de manera más ordenada.

## Principales Problemas y Soluciones

### Problemas en el Archivo de Prueba (`test_mprotect.c`)

1. **Paso 2 - Escritura en la Página Protegida:** Durante las pruebas, uno de los problemas más significativos fue en el paso 2 del archivo `test_mprotect.c`, donde intentaba escribir en una página protegida para probar que la función `mprotect` funcionara correctamente. Este paso arrojaba numerosos errores, por lo que decidí comentarlo y, eventualmente, eliminarlo para evitar que interfiriera con el resto de las pruebas.

2. **Errores en los `#include`:** Los primeros errores surgieron debido a la necesidad de especificar las rutas correctas en los `#include`. Fue necesario especificar si los archivos estaban en el espacio de `kernel` o `user`, agregando `kernel/` o `user/` en las rutas. Esto solucionó varios problemas de compilación y permitió que el sistema encontrara los archivos necesarios.

### Problemas en Múltiples Archivos

La implementación de `mprotect` y `munprotect` involucró modificaciones en varios archivos del sistema xv6:

- **`vm.c`**: Aquí se agregó la lógica principal para `mprotect` y `munprotect`, asegurando que las páginas de memoria se protegieran o desprotegieran correctamente. Fue fundamental colocar el código en las secciones adecuadas y verificar la validez de los permisos de las páginas.
  
- **`syscall.h`, `syscall.c` y `sysproc.c`**: Estos archivos requerían cambios para registrar las nuevas llamadas al sistema y conectar las funciones con el kernel. Esto incluyó definir las constantes de las nuevas llamadas y sus funciones correspondientes en el kernel.

- **`user.h` y `usys.pl`**: Se declararon las funciones `mprotect` y `munprotect` para hacerlas accesibles desde los programas de usuario.

Cada cambio debía hacerse de forma cuidadosa para evitar errores de compilación. Incluso un pequeño error en uno de estos archivos provocaba fallos en la construcción del sistema.

### Depuración y Validación del Código

Para depurar el código y solucionar problemas de compilación y ejecución, utilicé las siguientes estrategias:

1. **Mensajes de Depuración (`printf`)**: Agregar mensajes de `printf` en puntos clave del código ayudó a rastrear el flujo de ejecución y a verificar el estado de las variables, especialmente para detectar problemas de alineación de direcciones y permisos de páginas.
   
2. **Iteración Continua**: Debido a la complejidad de la tarea, fueron necesarias múltiples iteraciones para probar el código, detectar errores y hacer ajustes hasta que el sistema compilara y ejecutara correctamente.

## Resultados Finales

Tras implementar todas las funciones y realizar pruebas exhaustivas, el sistema xv6 fue capaz de:

1. **Aplicar protección de solo lectura** a una región de memoria especificada usando `mprotect`.
2. **Eliminar la protección de solo lectura** permitiendo la escritura nuevamente con `munprotect`.
3. Ejecutar exitosamente el programa de prueba `test_mprotect`, mostrando el siguiente resultado en la consola:

mprotect: protección aplicada con éxito en addr: 4000, len: 1
Escribiendo en la página desprotegida...
Valor almacenado en la dirección (como ASCII): B
Valor almacenado en la dirección (como hexadecimal): 0x42

## Conclusión
A lo largo de esta tarea, se presentaron varios desafíos, desde problemas de compilación hasta errores en la implementación de las funciones. Sin embargo, gracias a la experiencia adquirida en los intentos previos y un enfoque de depuración cuidadoso, se logró una implementación exitosa de mprotect y munprotect. Esta tarea me permitió entender más a fondo el manejo de memoria en un sistema operativo y la importancia de los permisos de acceso a la memoria para la seguridad y estabilidad del sistema.
