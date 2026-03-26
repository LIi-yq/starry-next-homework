#include <unistd.h>
#include <stdio.h>
#include "../homework_common.h"

int main(void) {
    const char *tag = "HOMEWORK_PID_PPID";
    long pid1;
    long pid2;
    long ppid1;
    long ppid2;

    hw_title(tag);

    pid1 = (long)getpid();
    ppid1 = (long)getppid();
    pid2 = (long)getpid();
    ppid2 = (long)getppid();

    if (!hw_expect_gt_long(pid1, 0, tag, "pid1_invalid")) return 1;
    if (!hw_expect_gt_long(ppid1, 0, tag, "ppid1_invalid")) return 2;
    if (!hw_expect_eq_long(pid1, pid2, tag, "pid_changed")) return 3;
    if (!hw_expect_eq_long(ppid1, ppid2, tag, "ppid_changed")) return 4;
    if (!hw_expect_ne_long(pid1, ppid1, tag, "pid_equal_ppid")) return 5;

    hw_note("pid1=%ld", pid1);
    hw_note("ppid1=%ld", ppid1);
    hw_note("pid2=%ld", pid2);
    hw_note("ppid2=%ld", ppid2);

    if (!hw_expect_ge_long(pid1, 1, tag, "pid_too_small")) return 6;
    if (!hw_expect_ge_long(ppid1, 1, tag, "ppid_too_small")) return 7;

    hw_pass_msg(tag);
    return 0;
}