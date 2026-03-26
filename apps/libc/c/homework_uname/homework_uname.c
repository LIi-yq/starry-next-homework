#include <sys/utsname.h>
#include <stdio.h>
#include <string.h>
#include "../homework_common.h"

int main(void) {
    const char *tag = "HOMEWORK_UNAME";
    struct utsname u1;
    struct utsname u2;

    hw_title(tag);
    hw_zero(&u1, sizeof(u1));
    hw_zero(&u2, sizeof(u2));

    if (uname(&u1) != 0) {
        perror("uname_first");
        return 1;
    }
    if (uname(&u2) != 0) {
        perror("uname_second");
        return 2;
    }

    if (!hw_expect_string_nonempty(u1.sysname, tag, "sysname_empty")) return 3;
    if (!hw_expect_string_nonempty(u1.nodename, tag, "nodename_empty")) return 4;
    if (!hw_expect_string_nonempty(u1.release, tag, "release_empty")) return 5;
    if (!hw_expect_string_nonempty(u1.version, tag, "version_empty")) return 6;
    if (!hw_expect_string_nonempty(u1.machine, tag, "machine_empty")) return 7;

    if (!hw_expect_str_eq(u1.sysname, u2.sysname, tag, "sysname_changed")) return 8;
    if (!hw_expect_str_eq(u1.machine, u2.machine, tag, "machine_changed")) return 9;

    hw_note("sysname=%s", u1.sysname);
    hw_note("nodename=%s", u1.nodename);
    hw_note("release=%s", u1.release);
    hw_note("version=%s", u1.version);
    hw_note("machine=%s", u1.machine);

    if (strlen(u1.sysname) > 128) return 10;
    if (strlen(u1.machine) > 128) return 11;

    hw_pass_msg(tag);
    return 0;
}