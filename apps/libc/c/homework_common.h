#ifndef HOMEWORK_COMMON_H
#define HOMEWORK_COMMON_H

#include <errno.h>
#include <fcntl.h>
#include <signal.h>
#include <stdarg.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <time.h>
#include <unistd.h>

static inline void hw_title(const char *name) {
    printf("========== %s ==========\n", name);
}

static inline void hw_note(const char *fmt, ...) {
    va_list ap;
    va_start(ap, fmt);
    vprintf(fmt, ap);
    printf("\n");
    va_end(ap);
}

static inline void hw_fail_msg(const char *tag, const char *msg) {
    printf("%s_FAIL:%s\n", tag, msg);
}

static inline void hw_pass_msg(const char *tag) {
    printf("%s_OK\n", tag);
}

static inline int hw_expect_true(int cond, const char *tag, const char *msg) {
    if (!cond) {
        hw_fail_msg(tag, msg);
        return 0;
    }
    return 1;
}

static inline int hw_expect_false(int cond, const char *tag, const char *msg) {
    if (cond) {
        hw_fail_msg(tag, msg);
        return 0;
    }
    return 1;
}

static inline int hw_expect_eq_long(long a, long b, const char *tag, const char *msg) {
    if (a != b) {
        printf("%s_FAIL:%s expected=%ld actual=%ld\n", tag, msg, b, a);
        return 0;
    }
    return 1;
}

static inline int hw_expect_ne_long(long a, long b, const char *tag, const char *msg) {
    if (a == b) {
        printf("%s_FAIL:%s unexpected=%ld\n", tag, msg, a);
        return 0;
    }
    return 1;
}

static inline int hw_expect_ge_long(long a, long b, const char *tag, const char *msg) {
    if (a < b) {
        printf("%s_FAIL:%s actual=%ld lower=%ld\n", tag, msg, a, b);
        return 0;
    }
    return 1;
}

static inline int hw_expect_gt_long(long a, long b, const char *tag, const char *msg) {
    if (a <= b) {
        printf("%s_FAIL:%s actual=%ld lower=%ld\n", tag, msg, a, b);
        return 0;
    }
    return 1;
}

static inline int hw_expect_le_long(long a, long b, const char *tag, const char *msg) {
    if (a > b) {
        printf("%s_FAIL:%s actual=%ld upper=%ld\n", tag, msg, a, b);
        return 0;
    }
    return 1;
}

static inline int hw_expect_nonnull(const void *p, const char *tag, const char *msg) {
    if (p == NULL) {
        hw_fail_msg(tag, msg);
        return 0;
    }
    return 1;
}

static inline int hw_expect_string_nonempty(const char *s, const char *tag, const char *msg) {
    if (s == NULL || s[0] == '\0') {
        hw_fail_msg(tag, msg);
        return 0;
    }
    return 1;
}

static inline int hw_expect_str_eq(const char *a, const char *b, const char *tag, const char *msg) {
    if (a == NULL || b == NULL) {
        hw_fail_msg(tag, msg);
        return 0;
    }
    if (strcmp(a, b) != 0) {
        printf("%s_FAIL:%s left=%s right=%s\n", tag, msg, a, b);
        return 0;
    }
    return 1;
}

static inline long hw_timespec_to_ns(const struct timespec *ts) {
    return (long)ts->tv_sec * 1000000000L + (long)ts->tv_nsec;
}

static inline long hw_timeval_to_us(const struct timeval *tv) {
    return (long)tv->tv_sec * 1000000L + (long)tv->tv_usec;
}

static inline long hw_diff_timespec_ns(const struct timespec *a, const struct timespec *b) {
    return hw_timespec_to_ns(b) - hw_timespec_to_ns(a);
}

static inline long hw_diff_timeval_us(const struct timeval *a, const struct timeval *b) {
    return hw_timeval_to_us(b) - hw_timeval_to_us(a);
}

static inline void hw_fill_pattern(unsigned char *buf, size_t n, unsigned char seed) {
    size_t i = 0;
    for (i = 0; i < n; ++i) {
        buf[i] = (unsigned char)(seed + (unsigned char)(i % 251));
    }
}

static inline int hw_check_pattern(const unsigned char *buf, size_t n, unsigned char seed) {
    size_t i = 0;
    for (i = 0; i < n; ++i) {
        unsigned char expect = (unsigned char)(seed + (unsigned char)(i % 251));
        if (buf[i] != expect) {
            return 0;
        }
    }
    return 1;
}

static inline unsigned long hw_checksum(const unsigned char *buf, size_t n) {
    size_t i = 0;
    unsigned long sum = 0;
    for (i = 0; i < n; ++i) {
        sum = (sum * 131UL) + (unsigned long)buf[i];
    }
    return sum;
}

static inline int hw_write_all(int fd, const void *buf, size_t n) {
    const char *p = (const char *)buf;
    size_t done = 0;
    while (done < n) {
        ssize_t ret = write(fd, p + done, n - done);
        if (ret < 0) {
            return -1;
        }
        done += (size_t)ret;
    }
    return 0;
}

static inline int hw_read_once(int fd, void *buf, size_t n) {
    ssize_t ret = read(fd, buf, n);
    if (ret < 0) {
        return -1;
    }
    return (int)ret;
}

static inline int hw_remove_file(const char *path) {
    if (unlink(path) == 0) {
        return 0;
    }
    if (errno == ENOENT) {
        return 0;
    }
    return -1;
}

static inline void hw_make_path(char *out, size_t n, const char *name) {
    snprintf(out, n, "/tmp/%s_%ld.txt", name, (long)getpid());
}

static inline int hw_create_file_with_text(const char *path, const char *text) {
    int fd = open(path, O_CREAT | O_TRUNC | O_WRONLY, 0644);
    if (fd < 0) {
        return -1;
    }
    size_t len = strlen(text);
    int ok = hw_write_all(fd, text, len);
    close(fd);
    return ok;
}

static inline int hw_read_file_to_buffer(const char *path, char *buf, size_t n) {
    int fd = open(path, O_RDONLY, 0);
    int ret;
    if (fd < 0) {
        return -1;
    }
    ret = hw_read_once(fd, buf, n - 1);
    close(fd);
    if (ret < 0) {
        return -1;
    }
    buf[ret] = '\0';
    return ret;
}

static inline int hw_sleep_ms(long ms) {
    struct timespec req;
    req.tv_sec = ms / 1000;
    req.tv_nsec = (ms % 1000) * 1000000L;
    return nanosleep(&req, NULL);
}

static inline void hw_fill_text(char *buf, size_t n, char base) {
    size_t i = 0;
    if (n == 0) {
        return;
    }
    for (i = 0; i + 1 < n; ++i) {
        buf[i] = (char)(base + (char)(i % 26));
    }
    buf[n - 1] = '\0';
}

static inline int hw_same_prefix(const char *a, const char *b, size_t n) {
    size_t i = 0;
    for (i = 0; i < n; ++i) {
        if (a[i] != b[i]) {
            return 0;
        }
        if (a[i] == '\0' || b[i] == '\0') {
            return 1;
        }
    }
    return 1;
}

static inline void hw_print_bytes(const unsigned char *buf, size_t n) {
    size_t i = 0;
    for (i = 0; i < n; ++i) {
        printf("%02x", buf[i]);
        if (i + 1 < n) {
            printf(" ");
        }
    }
    printf("\n");
}

static inline void hw_zero(void *buf, size_t n) {
    memset(buf, 0, n);
}

static inline int hw_open_rw_create(const char *path) {
    return open(path, O_CREAT | O_TRUNC | O_RDWR, 0644);
}

static inline int hw_close_quiet(int fd) {
    if (fd >= 0) {
        return close(fd);
    }
    return 0;
}

static inline int hw_expect_fd_valid(int fd, const char *tag, const char *msg) {
    if (fd < 0) {
        printf("%s_FAIL:%s errno=%d\n", tag, msg, errno);
        return 0;
    }
    return 1;
}

static inline int hw_expect_errno_eq(int expect, const char *tag, const char *msg) {
    if (errno != expect) {
        printf("%s_FAIL:%s errno=%d expect=%d\n", tag, msg, errno, expect);
        return 0;
    }
    return 1;
}

static inline int hw_expect_mem_eq(const unsigned char *a, const unsigned char *b, size_t n, const char *tag, const char *msg) {
    size_t i = 0;
    for (i = 0; i < n; ++i) {
        if (a[i] != b[i]) {
            printf("%s_FAIL:%s idx=%zu a=%u b=%u\n", tag, msg, i, (unsigned)a[i], (unsigned)b[i]);
            return 0;
        }
    }
    return 1;
}

static inline int hw_stat_size(const char *path, off_t *size_out) {
    struct stat st;
    if (stat(path, &st) != 0) {
        return -1;
    }
    *size_out = st.st_size;
    return 0;
}

static inline int hw_truncate_file(int fd, off_t len) {
    return ftruncate(fd, len);
}

static inline int hw_flush_stdout(void) {
    return fflush(stdout);
}

static inline int hw_print_and_flush(const char *s) {
    if (fputs(s, stdout) == EOF) {
        return -1;
    }
    return hw_flush_stdout();
}

static inline unsigned long hw_spin_sum(unsigned long seed, int rounds) {
    int i = 0;
    unsigned long x = seed;
    for (i = 0; i < rounds; ++i) {
        x = x * 1103515245UL + 12345UL + (unsigned long)i;
        x ^= (x >> 7);
        x ^= (x << 11);
    }
    return x;
}

#endif