# Configuración de kernel.

## José Alejandro Grande Marín - 201602855

## Paso 1.
Instalar linux mint cinammon 22, virtualmente , con suficiente capacidad ram y nucleos.

## Paso 2.
Se continua con la configuración del kernel a modificar , se procede a descargar un kernel nuevo:

ejecutando el siguiente comando dentro de una terminal se nos generara un paquete comprimido .xz , siendo este el que contiene el kernel que se modificara.

```bash
wget https://www.kernel.org/pub/linux/kernel/v6.x/linux-6.8.tar.xz
```



Para descomprimir el archivo podemos utilizar el siguiente comando , al descomprimir el archivo se genera una carpeta con el nombre `linux-6.8` con el archivo descomprimido e identificando su ubicacion (esta puede ser la ubicacion a eleccion) nos iremos al archivo `Makefile` en el cual podemos modificar la linea que tiene por encabezado `EXTRAVERSION` para poder dar un nuevo alias al kernel y no confundirlo con el original, para este proyecto se agregara  `-49-usac1`.

```bash
tar -xf linux-6.8.tar.xz
```

Para que los cambios realizados para la identificacion del kernelse vean reflejados en el sistema operativo se ejecutaran los siguientes pasos:
1.- Instalaremos algunas dependecias/credenciales, ejecutando los siguientes comandos.

```bash
sudo apt-get install build-essential libncurses5-dev fakeroot wget bzip2 openssl
sudo apt-get install build-essential libncurses-dev bison flex libssl-dev libelf-dev
```

2.- Copiar el archivo de configuración desde el kernel principal.

```bash
cp -v /boot/config-$(uname -r) .config
```
3.- Actualizar el grub y reinicar.
```bash
sudo update-grub2
```

Al momento de reiniciar la maquina , se debe mostrar un menu en el inicio del sistema en donde nos aparecera el kernel que contendra el alias que le dimos y procedemos a seleccionarlo, ya dentro del sistema abriremos una terminal en la cual para validar sobre que kernel estamos ejecutaremos el siguiente comando `uname -r` esto nos mostrara en consola un mensaje como este `linux-6.8-49-usac1`.

![Kernel Configuration](https://github.com/AlejooMariin/SOPES2_PROYECTO1/blob/main/Documentaci%C3%B3n/imagenes/Imagen_1.jpg)

## Paso 3.
Configuración de symlinks.
1.- agregar al repositorio los archivos de interes
1.- configurar todos los archivos en las rutas similares a las del kernel original. 
2.- realizar el acceso del archivo que se encuentra en el repositorio a la ruta del kernel original.
3.- En la terminal ejecutar el comando `ln -s rutadondeestaelarchivo rutadondeestaraelsymlink`

![Symlink Configuration](https://github.com/AlejooMariin/SOPES2_PROYECTO1/blob/main/Documentaci%C3%B3n/imagenes/Imagen_2.png)

## Paso 4.
Conociendo el procedimiento de configurar symlinks, se realiza con todos los archivos de interes

Realizando todos los pasos mencionados ateriormente, para cada cambio que se realice y se suba al repositorio se recomienda ejecutar el archivo de compilacion.sh con el siguiente comando `sudo -s` y `bash compile_and_install.sh` ![Compilación](https://github.com/AlejooMariin/SOPES2_PROYECTO1/blob/main/Documentaci%C3%B3n/imagenes/Imagen_3.png) , para comprender la funcionalidad del archivo leerlo. y poder saber que aceptar y que no. 
