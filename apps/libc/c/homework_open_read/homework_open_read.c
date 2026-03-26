#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include "../homework_common.h"

int main(void) {
    const char *tag = "HOMEWORK_OPEN_READ";
    char path[128];
    char buf[256];
    const char *text = "starry_homework_open_read_text";
    int fd;
    int n;

    hw_title(tag);
    hw_make_path(path, sizeof(path), "homework_open_read");
    hw_remove_file(path);

    if (hw_create_file_with_text(path, text) != 0) {
        perror("create_file");
        return 1;
    }

    fd = open(path, O_RDONLY, 0);
    if (!hw_expect_fd_valid(fd, tag, "open_failed")) return 2;

    hw_zero(buf, sizeof(buf));
    n = hw_read_once(fd, buf, sizeof(buf) - 1);
    if (!hw_expect_ge_long(n, 0, tag, "read_failed")) {
        close(fd);
        return 3;
    }

    close(fd);
    hw_note("read_text=%s", buf);

    if (!hw_expect_str_eq(buf, text, tag, "content_mismatch")) return 4;
    if (hw_remove_file(path) != 0) return 5;

    hw_pass_msg(tag);
    return 0;
}