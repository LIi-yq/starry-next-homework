#include <signal.h>
#include <unistd.h>
#include <stdio.h>
#include "../homework_common.h"

static volatile sig_atomic_t g_basic_count = 0;

static void basic_handler(int signo) {
    g_basic_count++;
    write(STDOUT_FILENO, "basic_handler\n", 14);
    (void)signo;
}

int main(void) {
    const char *tag = "HOMEWORK_SIGNAL_BASIC";
    void (*old)(int);

    hw_title(tag);

    old = signal(SIGUSR1, basic_handler);
    if (!hw_expect_true(old != SIG_ERR, tag, "signal_register_failed")) return 1;

    if (raise(SIGUSR1) != 0) {
        perror("raise_first");
        return 2;
    }

    if (raise(SIGUSR1) != 0) {
        perror("raise_second");
        return 3;
    }

    if (!hw_expect_eq_long((long)g_basic_count, 2, tag, "handler_count_mismatch")) return 4;

    hw_note("basic_count=%ld", (long)g_basic_count);

    hw_pass_msg(tag);
    return 0;
}