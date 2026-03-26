#include <sys/mman.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include "../homework_common.h"

int main(void) {
    const char *tag = "HOMEWORK_MMAP_RW";
    size_t len = 8192;
    unsigned char *p;
    unsigned long sum1;
    unsigned long sum2;

    hw_title(tag);

    p = (unsigned char *)mmap(NULL, len, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
    if (!hw_expect_true(p != MAP_FAILED, tag, "mmap_failed")) return 1;

    hw_fill_pattern(p, len, 33);
    sum1 = hw_checksum(p, len);

    memset(p + 1024, 0x5A, 2048);
    sum2 = hw_checksum(p, len);

    hw_note("sum_before=%lu", sum1);
    hw_note("sum_after=%lu", sum2);

    if (!hw_expect_ne_long((long)sum1, (long)sum2, tag, "checksum_not_changed")) {
        munmap(p, len);
        return 2;
    }

    if (!hw_expect_eq_long((long)p[1024], 0x5A, tag, "write_verify_1")) {
        munmap(p, len);
        return 3;
    }

    if (!hw_expect_eq_long((long)p[2047], 0x5A, tag, "write_verify_2")) {
        munmap(p, len);
        return 4;
    }

    if (munmap(p, len) != 0) return 5;

    hw_pass_msg(tag);
    return 0;
}