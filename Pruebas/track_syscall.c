#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/syscall.h>
#include <string.h>
#include <time.h>  
#include <sys/types.h>

#define RESET "\033[0m"
#define RED "\033[31m"
#define GREEN "\033[32m"
#define BLUE "\033[34m"
#define YELLOW "\033[33m"
#define CYAN "\033[36m"

struct timespec64 {
    long tv_sec;   
    long tv_nsec;  
};

struct syscall_usage {
    unsigned long count;                    
    struct timespec64 time_last_used;       
};

#define MAX_SYS_CALLS 4
#define __NR_track_syscall_usage 549

int main() {
    struct syscall_usage statistics[MAX_SYS_CALLS];

    if (syscall(__NR_track_syscall_usage, statistics) < 0) {
        perror("Error en track_syscall_usage");
        return EXIT_FAILURE;
    }

    printf(BLUE "#########################################################################\n");
    for (int i = 0; i < MAX_SYS_CALLS; i++) {
        printf(YELLOW "Syscall ID " RESET YELLOW "%d" RESET ": " GREEN "Count = %lu\n" RESET, i, statistics[i].count);
    }
    printf(BLUE "#########################################################################\n");

    return EXIT_SUCCESS;
}

