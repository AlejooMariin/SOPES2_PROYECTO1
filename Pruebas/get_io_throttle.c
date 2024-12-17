#include <stdio.h>
#include <stdlib.h> // Agrega este encabezado para atoi
#include <unistd.h>
#include <sys/syscall.h>
#include <errno.h>
#include <string.h>

#define RESET "\033[0m"
#define RED "\033[31m"
#define GREEN "\033[32m"
#define BLUE "\033[34m"
#define YELLOW "\033[33m"
#define CYAN "\033[36m"
#define SYSCALL_GET_IO_THROTTLE 550 

struct io_stats {
    unsigned long bytes_read;
    unsigned long bytes_written;
    unsigned long read_syscalls;
    unsigned long write_syscalls;
    unsigned long io_wait_time; 
};

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Uso: %s <PID>\n", argv[0]);
        return -1;
    }

    pid_t pid = atoi(argv[1]); 
    struct io_stats stats;

    if (syscall(SYSCALL_GET_IO_THROTTLE, pid, &stats) == -1) {
        perror("Error en alejo_get_io_throttle");
        return errno;
    }

    printf(BLUE "#########################################################################\n");
    printf(CYAN "Estadísticas de I/O para PID " RESET YELLOW "%d:\n" RESET, pid);
    printf(YELLOW "Bytes leídos:      " RESET GREEN "%lu\n" RESET, stats.bytes_read);
    printf(YELLOW "Bytes escritos:    " RESET GREEN "%lu\n" RESET, stats.bytes_written);
    printf(YELLOW "Syscalls de lectura: " RESET GREEN "%lu\n" RESET, stats.read_syscalls);
    printf(YELLOW "Syscalls de escritura: " RESET GREEN "%lu\n" RESET, stats.write_syscalls);
    printf(BLUE "#########################################################################\n");


    return 0;
}

