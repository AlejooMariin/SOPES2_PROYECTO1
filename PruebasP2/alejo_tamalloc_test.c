
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/syscall.h>
#include <errno.h>
#include <time.h>

#define RESET "\033[0m"
#define RED "\033[31m"
#define GREEN "\033[32m"
#define BLUE "\033[34m"
#define YELLOW "\033[33m"
#define CYAN "\033[36m"

#define SYS_TAMALLOC 551
int main() {
    printf(GREEN "#########################################################################\n");    
    printf("PID: %d asignado a alejo_Tamalloc.\n", getpid());

    printf("Implementación de Tamalloc para asignación de memoria. Presione ENTER para continuar...\n");
    printf(GREEN "#########################################################################\n");    
    getchar();

    size_t total_size = 10 * 1024 * 1024; 

    // Use the tamalloc syscall
    char *buffer = (char *)syscall(SYS_TAMALLOC, total_size);
    if ((long)buffer < 0) {
        perror("Error en Tamalloc");
        return 1;
    }
    printf(GREEN "#########################################################################\n");    
    printf(RESET BLUE "Alojamiento de memoria (%zu bytes) usando Tamalloc en la dirección: %p\n", total_size, buffer);
    printf(RESET BLUE "Presione ENTER para comenzar a leer la memoria byte a byte...\n");
    printf(RESET GREEN "#########################################################################\n");    
    getchar();

    srand(time(NULL));

    // Read memory byte by byte and verify it is zero
    for (size_t i = 0; i < total_size; i++) {
        char t = buffer[i]; // triggers lazy allocation (with zeroing :D )
        if (t != 0) {
            printf("ERROR FATAL: La memoria en el byte %zu no se inicializó a 0.\n", i);
            return 10;
        }

        //Write a random A-Z char to trigger CoW
        char random_letter = 'A' + (rand() % 26);
        buffer[i] = random_letter;

        if (i % (1024 * 1024) == 0 && i > 0) { // Every 1 MB
            printf(GREEN "#########################################################################\n");    
            printf(RESET YELLOW "%zu MB Comprobados\n", i / (1024 * 1024));
            printf(RESET GREEN "#########################################################################\n");    
            sleep(1);
        }
    }

    printf("Se verificó que toda la memoria se inicializó a cero. Presione ENTER para salir.\n");
    getchar();
    return 0;
}
