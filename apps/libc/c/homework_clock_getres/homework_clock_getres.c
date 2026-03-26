#include <time.h>
#include <stdio.h>
#include "../homework_common.h"

static int check_one(clockid_t id, const char *name) {
    struct timespec ts;
    if (clock_getres(id, &ts) != 0) {
        perror(name);
        return 0;
    }
    hw_note("%s_sec=%ld", name, (long)ts.tv_sec);
    hw_note("%s_nsec=%ld", name, (long)ts.tv_nsec);
    if (ts.tv_sec < 0) return 0;
    if (ts.tv_nsec < 0) return 0;
    if (ts.tv_nsec > 999999999L) return 0;
    return 1;
}

int main(void) {
    const char *tag = "HOMEWORK_CLOCK_GETRES";

    hw_title(tag);

    if (!check_one(CLOCK_REALTIME, "clock_realtime")) return 1;
    if (!check_one(CLOCK_MONOTONIC, "clock_monotonic")) return 2;

    hw_pass_msg(tag);
    return 0;
}