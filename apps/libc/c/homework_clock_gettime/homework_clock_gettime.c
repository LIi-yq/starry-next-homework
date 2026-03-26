#include <time.h>
#include <stdio.h>
#include "../homework_common.h"

static int read_monotonic(struct timespec *ts) {
    return clock_gettime(CLOCK_MONOTONIC, ts);
}

static int read_realtime(struct timespec *ts) {
    return clock_gettime(CLOCK_REALTIME, ts);
}

int main(void) {
    const char *tag = "HOMEWORK_CLOCK_GETTIME";
    struct timespec m1;
    struct timespec m2;
    struct timespec r1;
    struct timespec r2;
    long diff_m;
    long diff_r;

    hw_title(tag);

    if (read_monotonic(&m1) != 0) return 1;
    if (read_realtime(&r1) != 0) return 2;
    if (hw_sleep_ms(20) != 0) return 3;
    if (read_monotonic(&m2) != 0) return 4;
    if (read_realtime(&r2) != 0) return 5;

    diff_m = hw_diff_timespec_ns(&m1, &m2);
    diff_r = hw_diff_timespec_ns(&r1, &r2);

    hw_note("monotonic_diff_ns=%ld", diff_m);
    hw_note("realtime_diff_ns=%ld", diff_r);

    if (!hw_expect_gt_long(diff_m, 0, tag, "monotonic_not_increasing")) return 6;
    if (!hw_expect_gt_long(diff_r, 0, tag, "realtime_not_increasing")) return 7;
    if (!hw_expect_le_long(m1.tv_nsec, 999999999L, tag, "m1_nsec_invalid")) return 8;
    if (!hw_expect_le_long(m2.tv_nsec, 999999999L, tag, "m2_nsec_invalid")) return 9;

    hw_pass_msg(tag);
    return 0;
}