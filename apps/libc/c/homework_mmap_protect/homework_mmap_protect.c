#include <sys/mman.h>
#include <unistd.h>
#include <stdio.h>
#include "../homework_common.h"

int main(void) {
    const char *tag = "HOMEWORK_MMAP_PROTECT";
    size_t len = 4096;
    unsigned char *p;
    int ret;

    hw_title(tag);

    p = (unsigned char *)mmap(NULL, len, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
    if (!hw_expect_true(p != MAP_FAILED, tag, "mmap_failed")) return 1;

    p[0] = 0x12;
    p[1] = 0x34;

    ret = mprotect(p, len, PROT_READ);
    if (!hw_expect_eq_long(ret, 0, tag, "mprotect_read_failed")) {
        munmap(p, len);
        return 2;
    }

    if (!hw_expect_eq_long((long)p[0], 0x12, tag, "read_after_mprotect_0")) {
        munmap(p, len);
        return 3;
    }

    if (!hw_expect_eq_long((long)p[1], 0x34, tag, "read_after_mprotect_1")) {
        munmap(p, len);
        return 4;
    }

    ret = mprotect(p, len, PROT_READ | PROT_WRITE);
    if (!hw_expect_eq_long(ret, 0, tag, "mprotect_restore_failed")) {
        munmap(p, len);
        return 5;
    }

    p[2] = 0x56;
    if (!hw_expect_eq_long((long)p[2], 0x56, tag, "write_after_restore_failed")) {
        munmap(p, len);
        return 6;
    }

    if (munmap(p, len) != 0) return 7;

    hw_pass_msg(tag);
    return 0;
}