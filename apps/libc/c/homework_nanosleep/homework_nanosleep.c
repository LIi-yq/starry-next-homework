#include <time.h>
#include <stdio.h>
#include "../homework_common.h"

int main(void) {
    const char *tag = "HOMEWORK_NANOSLEEP";
    struct timespec before;
    struct timespec after;
    struct timespec req;
    long diff_ns;

    hw_title(tag);

    req.tv_sec = 0;
    req.tv_nsec = 30000000L;

    if (clock_gettime(CLOCK_MONOTONIC, &before) != 0) {
        perror("clock_gettime_before");
        return 1;
    }

    if (nanosleep(&req, NULL) != 0) {
        perror("nanosleep");
        return 2;
    }

    if (clock_gettime(CLOCK_MONOTONIC, &after) != 0) {
        perror("clock_gettime_after");
        return 3;
    }

    diff_ns = hw_diff_timespec_ns(&before, &after);

    hw_note("requested_ns=%ld", (long)req.tv_nsec);
    hw_note("actual_ns=%ld", diff_ns);

    if (!hw_expect_gt_long(diff_ns, 10000000L, tag, "sleep_too_short")) return 4;
    if (!hw_expect_le_long(diff_ns, 1000000000L, tag, "sleep_too_long")) return 5;

    hw_pass_msg(tag);
    return 0;
}