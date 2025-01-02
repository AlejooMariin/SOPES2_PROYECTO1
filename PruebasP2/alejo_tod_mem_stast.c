#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/syscall.h>
#include <unistd.h>
#include <errno.h>

#define RESET "\033[0m"
#define RED "\033[31m"
#define GREEN "\033[32m"
#define BLUE "\033[34m"
#define YELLOW "\033[33m"
#define CYAN "\033[36m"

#define SYS_alejo_tod_mem_totals 553

// Estructura para los totales de memoria
struct total_mem_stats {
    unsigned long total_reserved_mb;   // Total de memoria reservada en MB
    unsigned long total_committed_mb;  // Total de memoria comprometida en MB
};

int main() {
    struct total_mem_stats totals;

    // Llamar a la syscall
    int result = syscall(SYS_alejo_tod_mem_totals, &totals);

    if (result < 0) {
        perror("Error al invocar la syscall");
        return EXIT_FAILURE;
    }

    // Imprimir los totales
    printf(GREEN "#########################################################################\n");    
    printf(RESET BLUE "Totales del sistema:\n");
    printf(RESET BLUE "  Memoria Reservada Total:" RESET YELLOW "%lu MB\n", totals.total_reserved_mb);
    printf(RESET BLUE "  Memoria Comprometida Total:" RESET YELLOW "%lu MB\n", totals.total_committed_mb);
    printf(RESET GREEN "#########################################################################\n");    

    return EXIT_SUCCESS;
}

