#define _GNU_SOURCE
#include <sys/syscall.h>
#include <unistd.h>
#include <stdio.h>

int main(void) {
    long tid = syscall(SYS_gettid);
    long pid = (long)getpid();
    long ppid = (long)getppid();

    if (tid <= 0) {
        printf("GETTID_FAIL\n");
        return 1;
    }

    printf("GETTID_OK pid=%ld tid=%ld ppid=%ld\n", pid, tid, ppid);
    return 0;
}