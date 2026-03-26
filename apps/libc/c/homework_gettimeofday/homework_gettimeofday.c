#include <sys/time.h>
#include <stdio.h>
#include "../homework_common.h"

int main(void) {
    const char *tag = "HOMEWORK_GETTIMEOFDAY";
    struct timeval tv1;
    struct timeval tv2;
    long diff_us;

    hw_title(tag);

    if (gettimeofday(&tv1, NULL) != 0) {
        perror("gettimeofday_first");
        return 1;
    }

    if (hw_sleep_ms(15) != 0) {
        perror("nanosleep");
        return 2;
    }

    if (gettimeofday(&tv2, NULL) != 0) {
        perror("gettimeofday_second");
        return 3;
    }

    diff_us = hw_diff_timeval_us(&tv1, &tv2);

    hw_note("tv1_sec=%ld", (long)tv1.tv_sec);
    hw_note("tv1_usec=%ld", (long)tv1.tv_usec);
    hw_note("tv2_sec=%ld", (long)tv2.tv_sec);
    hw_note("tv2_usec=%ld", (long)tv2.tv_usec);
    hw_note("diff_us=%ld", diff_us);

    if (!hw_expect_gt_long(diff_us, 0, tag, "time_not_increasing")) return 4;
    if (!hw_expect_le_long(tv1.tv_usec, 999999L, tag, "tv1_usec_invalid")) return 5;
    if (!hw_expect_le_long(tv2.tv_usec, 999999L, tag, "tv2_usec_invalid")) return 6;

    hw_pass_msg(tag);
    return 0;
}