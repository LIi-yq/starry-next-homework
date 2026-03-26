#include <signal.h>
#include <unistd.h>
#include <stdio.h>
#include "../homework_common.h"

static volatile sig_atomic_t g_alarm_count = 0;

static void alarm_handler(int signo) {
    g_alarm_count++;
    write(STDOUT_FILENO, "alarm_handler\n", 14);
    (void)signo;
}

int main(void) {
    const char *tag = "HOMEWORK_SIGNAL_ALARM";
    void (*old)(int);
    unsigned int left;

    hw_title(tag);

    old = signal(SIGALRM, alarm_handler);
    if (!hw_expect_true(old != SIG_ERR, tag, "signal_alarm_register_failed")) return 1;

    alarm(1);
    hw_sleep_ms(1200);

    if (!hw_expect_eq_long((long)g_alarm_count, 1, tag, "alarm_count_not_one")) return 2;

    left = alarm(0);
    if (!hw_expect_eq_long((long)left, 0, tag, "alarm_cancel_left_not_zero")) return 3;

    hw_note("alarm_count=%ld", (long)g_alarm_count);

    hw_pass_msg(tag);
    return 0;
}