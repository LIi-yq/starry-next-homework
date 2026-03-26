#include <sys/utsname.h>
#include <stdio.h>
#include <string.h>

int main(void) {
    struct utsname u;

    if (uname(&u) != 0) {
        perror("uname");
        return 1;
    }

    if (strlen(u.sysname) == 0 || strlen(u.machine) == 0) {
        printf("UNAME_FAIL\n");
        return 2;
    }

    printf("UNAME_OK sys=%s release=%s machine=%s\n",
           u.sysname, u.release, u.machine);
    return 0;
}