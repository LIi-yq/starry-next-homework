#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include "../homework_common.h"

int main(void) {
    const char *tag = "HOMEWORK_DUP_DUP2";
    char path[128];
    char buf[128];
    const char *text = "dup_and_dup2_test_payload";
    int fd;
    int fd2;
    int fd3;
    int n;

    hw_title(tag);
    hw_make_path(path, sizeof(path), "homework_dup");
    hw_remove_file(path);

    fd = hw_open_rw_create(path);
    if (!hw_expect_fd_valid(fd, tag, "open_rw_create_failed")) return 1;

    if (hw_write_all(fd, text, strlen(text)) != 0) {
        close(fd);
        return 2;
    }

    if (lseek(fd, 0, SEEK_SET) < 0) {
        close(fd);
        return 3;
    }

    fd2 = dup(fd);
    if (!hw_expect_fd_valid(fd2, tag, "dup_failed")) {
        close(fd);
        return 4;
    }

    fd3 = dup2(fd, fd2 + 1);
    if (!hw_expect_fd_valid(fd3, tag, "dup2_failed")) {
        close(fd2);
        close(fd);
        return 5;
    }

    hw_zero(buf, sizeof(buf));
    n = hw_read_once(fd2, buf, sizeof(buf) - 1);
    if (!hw_expect_ge_long(n, 0, tag, "read_dup_fd_failed")) return 6;

    hw_note("dup_read=%s", buf);

    if (!hw_expect_str_eq(buf, text, tag, "dup_content_mismatch")) return 7;

    close(fd3);
    close(fd2);
    close(fd);
    hw_remove_file(path);

    hw_pass_msg(tag);
    return 0;
}