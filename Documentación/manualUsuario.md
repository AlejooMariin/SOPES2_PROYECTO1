# Manual de Usuario

## Introducción
Comprender y manipular las funcionalidades internas del kernel es clave para optimizar el rendimiento y saber como funcionan los SO. El objetivo de este proyecto fue desarrollar módulos del kernel Linux mint que proporcionen información del sistema, tales como estadísticas del cpu, el almacenamiento y la ram.

## Objetivos del Proyecto
- Desarrollar modulos del kernel de linux para recopilar estadísticas del sistema.
- Exponer la información del sistema de forma accesible.
- Documentar y validar el funcionamiento de los módulos.

## Bienvenida del sistema
Al modificar el kernel se le agrega una bienvenida la cual puede ser al gusto del usuario. para este proyecto se agrega la siguiente.
![Mensaje de Bienvenida](https://github.com/AlejooMariin/SOPES2_PROYECTO1/blob/main/Documentaci%C3%B3n/imagenes/Imagen_8.png)

## Ejecucion de Pruebas Syscall

Para obtener los resultados esperados de la logica de las syscall se necesitan realizar dos pasos
1.- Colocarnos sobre la carpeta pruebas dentro del repositorio y generamos los ejecutables con el siguiente comando 
```bash
gcc -o nombre_archivo_ejecutable nombre_arhivo.c
```
![Generar Ejecutable](https://github.com/AlejooMariin/SOPES2_PROYECTO1/blob/main/Documentaci%C3%B3n/imagenes/Imagen_5.png)

2.- correr el ejecutable con el siguiente comando
```bash
sudo ./nombre_archivo_ejecutable
```
Correr Ejecutable y obtener Resultados
![Correr Ejecutable](https://github.com/AlejooMariin/SOPES2_PROYECTO1/blob/main/Documentaci%C3%B3n/imagenes/Imagen_6.png)


## Ejecucion de Modulos

Redireccionamiento a la ruta correcta
```bash
make -C /lib/modules/6.8.0-49-usac1/build M=/home/alejo/Documents/REPOSITORIO/SOPES2_PROYECTO1/Modulos/CPU modules
```

Insertar el modulo
```bash
sudo insmod cpu.ko
```

Obtener resultado
```bash
cat /proc/cpu_so2_201602855
```

Resultados 

![Correr Ejecutable](https://github.com/AlejooMariin/SOPES2_PROYECTO1/blob/main/Documentaci%C3%B3n/imagenes/Imagen_7.png)


## Comentario General 

Las funcionalidades desarrolladas para obtener las estadisticas esperadas pueden llegar a ser funcionalidades mas optimas y exactas, por lo que las soluciones vistas en este proyecto pueden no son definitivas , con un poco mas de investigacion y analisis se pueden llegar a obtener mejores resultados a lo interno e iniciar con mejores practicas a nivel de codigo.
