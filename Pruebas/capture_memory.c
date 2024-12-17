#include <stdio.h>
#include <unistd.h>
#include <sys/syscall.h>

#define RESET "\033[0m"
#define RED "\033[31m"
#define GREEN "\033[32m"
#define BLUE "\033[34m"
#define YELLOW "\033[33m"

struct mem_snapshot {
    unsigned long total_memory;
    unsigned long free_memory;
    unsigned long active_pages;
    unsigned long inactive_pages;

};

int main() {
    struct mem_snapshot snapshot;
    if (syscall(548, &snapshot) == 0) {

    printf(BLUE "#########################################################################\n");    
    printf(YELLOW "Total Memory: " RESET GREEN "%lu KB\n" RESET, snapshot.total_memory);
    printf(YELLOW "Free Memory: " RESET GREEN "%lu KB\n" RESET, snapshot.free_memory);
    printf(YELLOW "Active Pages: " RESET GREEN "%lu\n" RESET, snapshot.active_pages);
    printf(YELLOW "Inactive Pages: " RESET GREEN "%lu\n" RESET, snapshot.inactive_pages);
    printf(BLUE "#########################################################################\n");   

    } else {
        perror(RED "Syscall error");
    }
    return 0;
}
