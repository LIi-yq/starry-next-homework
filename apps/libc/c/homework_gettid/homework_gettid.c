#define _GNU_SOURCE
#include <sys/syscall.h>
#include <unistd.h>
#include <stdio.h>
#include "../homework_common.h"

static long call_gettid(void) {
    return syscall(SYS_gettid);
}

int main(void) {
    const char *tag = "HOMEWORK_GETTID";
    long tid1;
    long tid2;
    long pid;
    long ppid;

    hw_title(tag);

    tid1 = call_gettid();
    tid2 = call_gettid();
    pid = (long)getpid();
    ppid = (long)getppid();

    if (!hw_expect_gt_long(tid1, 0, tag, "tid1_invalid")) return 1;
    if (!hw_expect_gt_long(tid2, 0, tag, "tid2_invalid")) return 2;
    if (!hw_expect_eq_long(tid1, tid2, tag, "tid_changed_in_same_thread")) return 3;
    if (!hw_expect_gt_long(pid, 0, tag, "pid_invalid")) return 4;
    if (!hw_expect_gt_long(ppid, 0, tag, "ppid_invalid")) return 5;

    hw_note("pid=%ld", pid);
    hw_note("ppid=%ld", ppid);
    hw_note("tid=%ld", tid1);

    if (!hw_expect_ne_long(pid, -1, tag, "pid_minus_one")) return 6;
    if (!hw_expect_ne_long(tid1, -1, tag, "tid_minus_one")) return 7;

    hw_pass_msg(tag);
    return 0;
}