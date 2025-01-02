# Manual Técnico.

## José Alejandro Grande Marín - 201602855

## Configuraciones 

[Configuración del Kernel](https://github.com/AlejooMariin/SOPES2_PROYECTO1/blob/main/Documentaci%C3%B3n/configKernel.md)

## Archivos involucrados 
    - syscall_64.tbl 

    - syscalls.h 
    - Kernel 
    - usac (carpeta ajena al kernel) para el almacenamiento de los archivos con sysalls
    - Makefile 

## Errores presentados

## Error 1.

Uno de los errores que se me presentaron fueron por temas de referenciar el nombre del archivo al makefile dando como error que no encontraba la referencia y el error se daba al compilar 

Se soluciono referenciando el archivo.o al makefile

luego se ejecuto y funciono correctamente


# Uso de las syscalls

Creacion de ejecutables
![archivos ejecutable](https://github.com/AlejooMariin/SOPES2_PROYECTO1/blob/main/Documentaci%C3%B3n/imagenes/Imagen_1.jpeg)


Ejecucion de archivos
![archivos ejecutable](https://github.com/AlejooMariin/SOPES2_PROYECTO1/blob/main/Documentaci%C3%B3n/imagenes/Imagen_2.jpeg)


Salida de archivo

![archivos ejecutable](https://github.com/AlejooMariin/SOPES2_PROYECTO1/blob/main/Documentaci%C3%B3n/imagenes/Imagen_3.jpeg)

# Cronograma/Bitacora.

### Dia 1: Investigacion de estructura de listas en kernel y maneras de limitar recursos a procesos.
Investigacion sobre las funcionalidades de listas

### Dia 2: Diseño e implementacion de las estructuras de datos para la lista.
implementacion y pruebas de las listas.

### Dia 2-3: desarrollo de limitaciones de memoria
  desarrollo 

### Dia 4: Validaciones de errores de argumentos y runtime de las syscalls.
validacion de errores

### Dia 7: Pruebas resulucion de errores y elaboracion de documentacion
Generacion de documentacion 



# Comentario personal
El proyecto en general es una buena metodologia para el aprendisaje practico para las personas ya que llevaron un tipo de secuencia en la que cada fase tenia su nivel de complejidad siendo la primer fase el nucleo del resto y asi pudiendo estar mas enfocados en cada fase con los temas correspondientes, apesar de los errores y fallos sobre compilaciones, referencias y ejecuciones por ser procesos muy similares estos han podido ser parte de la practica 

El curso en general es un curso interesante, porque nos vamos a una etapa intermedia a lo que es el nivel maquina y el nivel de un usuario siendo una parte intermedia que nos permite entender un poco mas las funcionalidades abstractas del sistema nos permiten realizar nuestras logicas desde las logicas en las que fueron programadas. 