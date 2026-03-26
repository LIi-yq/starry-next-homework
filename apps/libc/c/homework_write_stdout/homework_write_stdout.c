#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include "../homework_common.h"

int main(void) {
    const char *tag = "HOMEWORK_WRITE_STDOUT";
    char msg1[64];
    char msg2[64];
    ssize_t ret1;
    ssize_t ret2;

    hw_title(tag);

    hw_fill_text(msg1, sizeof(msg1), 'A');
    hw_fill_text(msg2, sizeof(msg2), 'a');

    ret1 = write(STDOUT_FILENO, msg1, strlen(msg1));
    ret2 = write(STDOUT_FILENO, "\n", 1);
    if (ret1 < 0 || ret2 < 0) {
        perror("write_stdout_first");
        return 1;
    }

    ret1 = write(STDOUT_FILENO, msg2, strlen(msg2));
    ret2 = write(STDOUT_FILENO, "\n", 1);
    if (ret1 < 0 || ret2 < 0) {
        perror("write_stdout_second");
        return 2;
    }

    if (hw_print_and_flush("HOMEWORK_WRITE_STDOUT_CHECK\n") != 0) {
        perror("flush_stdout");
        return 3;
    }

    if (!hw_expect_gt_long((long)strlen(msg1), 0, tag, "msg1_empty")) return 4;
    if (!hw_expect_gt_long((long)strlen(msg2), 0, tag, "msg2_empty")) return 5;

    hw_pass_msg(tag);
    return 0;
}