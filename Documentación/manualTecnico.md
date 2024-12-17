# Manual Técnico.

## José Alejandro Grande Marín - 201602855

## Error 1.


El siguiente error se debe a que no se linkeo correctamente el archivo del repositorio al kernel original , lo que ocacionaba que este no encontrara las funciones ya que no estaban siendo agregadas en el archivo original , porque este no era el archivo que estaba sufriendo los cambios.

la solucion al error es ejecutar el siguiente comando 
```bash
ln -s rutadondeestaelarchivo rutadondeestaraelsymlink
```

![Kernel Configuration](https://github.com/AlejooMariin/SOPES2_PROYECTO1/blob/main/Documentaci%C3%B3n/imagenes/Imagen_4.jepg)

# Cronograma/Bitacora.

### Dia 1: Compilación y modificación básica del kernel.
08/12/2024 Configuración de kernel, errores con symlinks y usando como base grabaciones de laboratorios, lectura de documentación.

### Dia 2: Desarrollo de módulos personalizados del kernel.
09/12/2024 y 10/12/2024 Desarrollo y compilación del modulo que devuelve información de archivos de pruebas para la ram.

### Dia 3-5: Creación de las syscalls en el kernel
11/12/2024 y 12/12/24  desarrollo 
de la syscall que devolviera los valores solicitados para la ram.

### Dia 6: Pruebas y ajustes de la solución.
13/12/24 al 15/12/2024 Desarrollo de modulos ram,cpu y disk.

### Dia 7: Documentación final y presentación del proyecto
16/12/2024 Escritura de manuales técnico y de usuario.
