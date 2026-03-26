#include <sys/mman.h>
#include <unistd.h>
#include <stdio.h>
#include "../homework_common.h"

int main(void) {
    const char *tag = "HOMEWORK_MMAP_BASIC";
    size_t len = 4096;
    unsigned char *p;

    hw_title(tag);

    p = (unsigned char *)mmap(NULL, len, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
    if (!hw_expect_true(p != MAP_FAILED, tag, "mmap_failed")) return 1;

    hw_fill_pattern(p, len, 7);

    if (!hw_expect_true(hw_check_pattern(p, len, 7), tag, "pattern_check_failed")) {
        munmap(p, len);
        return 2;
    }

    hw_note("checksum=%lu", hw_checksum(p, len));

    if (munmap(p, len) != 0) {
        perror("munmap");
        return 3;
    }

    hw_pass_msg(tag);
    return 0;
}