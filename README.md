# Tarea 4: Implementación de Permisos Básicos en xv6

## **Nombre:** Matías Vanderschueren  
### **Curso:** Sistemas Operativos  
### **Profesor:** Sebastián Saez  

---

## **1. Introducción**

La tarea consistió en implementar un sistema de permisos básico en el sistema operativo xv6. Este sistema debía permitir modificar archivos para tener acceso de solo lectura, lectura/escritura o marcar un archivo como inmutable. A lo largo del desarrollo, enfrentamos numerosos problemas de compilación, errores lógicos y conflictos al ejecutar `make qemu`.

---

## **2. Objetivo**

1. Modificar la estructura de inodos para incluir permisos de archivos.
2. Validar permisos en operaciones de apertura, lectura y escritura.
3. Implementar la llamada al sistema `chmod` para gestionar permisos.
4. Manejar un permiso especial que marque los archivos como inmutables.

---

## **3. Desarrollo**

### **3.1 Modificaciones Realizadas**

#### a) Estructura de `inode` y `dinode`
Se agregó un campo `permissions` en `inode` y `dinode` para almacenar los permisos:
```c
#define PERM_READ  1
#define PERM_WRITE 2
#define PERM_IMMUTABLE 5
```
Este cambio implicó actualizar `fs.h` y los archivos relacionados con el manejo de inodos.

#### b) Implementación de `sys_chmod`
La nueva función `sys_chmod` permite cambiar los permisos de un archivo. Se añadieron validaciones para evitar que se cambien permisos en archivos marcados como inmutables:
```c
uint64 sys_chmod(void) {
    char path[MAXPATH];
    int mode;
    struct inode *ip;

    if (argstr(0, path, MAXPATH) < 0 || argint(1, &mode) < 0 || mode < 0) return -1;

    begin_op();
    if ((ip = namei(path)) == 0) {
        end_op();
        return -1;
    }
    ilock(ip);
    if (ip->permissions == PERM_IMMUTABLE) {
        iunlockput(ip);
        end_op();
        return -1;
    }
    ip->permissions = mode;
    iupdate(ip);
    iunlockput(ip);
    end_op();
    return 0;
}
```

#### c) Modificaciones en `sys_open`
Se añadieron validaciones para:
- Excluir la consola (`console`) de las restricciones de permisos.
- Verificar permisos antes de abrir archivos:
```c
if (namecmp(path, "console") == 0) {
    omode = O_RDWR; // Excluir consola
} else {
    if(ip->permissions == PERM_IMMUTABLE && omode != O_RDONLY) {
        printf("sys_open: archivo inmutable %s no puede abrirse para escritura
", path);
        iunlockput(ip);
        end_op();
        return -1;
    }
}
```

#### d) Validaciones en `file.c`
Se añadieron verificaciones en `fileread` y `filewrite` para confirmar permisos antes de operar:
```c
if((f->ip->permissions & PERM_READ) == 0) return -1; // Validación en fileread
if((f->ip->permissions & PERM_WRITE) == 0) return -1; // Validación en filewrite
```

---

### **3.2 Iteraciones y Problemas Encontrados**

#### a) Problemas de Compilación
- **Errores en `argint`:** Inicialmente, no devolvía valores adecuados en caso de error. Se solucionó implementando un retorno explícito:
```c
int argint(int n, int *ip) {
    if (n < 0 || n >= MAXARG) return -1;
    *ip = argraw(n);
    return 0;
}
```

- **Errores de dependencias:** Se solucionaron ajustando `#include` y asegurando compatibilidad en archivos relacionados con inodos.

#### b) Bucle Infinito en Consola
Al ejecutar `make qemu`, la consola de xv6 mostró el mensaje:
```
sys_open: permiso denegado para escribir en console
```
Esto se resolvió excluyendo explícitamente la consola de las validaciones en `sys_open`.

#### c) Errores en `mkfs`
La estructura `dinode` no estaba alineada correctamente. Se ajustó en `fs.h`:
```c
struct dinode {
    ...
    int permissions; // Permisos añadidos
};
```

---

## **4. Resultados**

1. **Compilación Exitosa:** Luego de múltiples iteraciones y ajustes, el sistema compiló correctamente tras un `make clean` y `make`.
2. **Ejecución Parcial:** La consola de xv6 se ejecuta con `make qemu`, pero sigue mostrando un bucle infinito relacionado con permisos de la consola.

---

## **5. Dificultades y Lecciones Aprendidas**

#### Dificultades:
- **Errores Recurrentes:** Las iteraciones frecuentes en `sys_open` y `sys_chmod` fueron un desafío, ya que pequeños errores lógicos afectaban la funcionalidad general.
- **Mensajes en Bucle:** Resolver el problema del bucle infinito en la consola tomó tiempo y análisis detallado.

#### Lecciones:
- **Paciencia y Persistencia:** La clave fue iterar paso a paso, entender los errores y resolverlos metódicamente.
- **Validaciones Claras:** Es fundamental validar condiciones específicas (como excluir la consola) para evitar errores inesperados.

---

## **6. Conclusión**

Aunque logramos implementar los permisos básicos en xv6, aún persisten problemas relacionados con la consola y la ejecución completa del sistema. Este proyecto destacó la importancia de las validaciones y pruebas exhaustivas en sistemas operativos.
