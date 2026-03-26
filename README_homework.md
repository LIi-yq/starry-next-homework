# Starry-next Homework Supplement

## 1. Project Overview

This homework is based on the `starry-next` baseline repository.

The main goal of this homework is not to redesign the whole kernel, but to extend the repository with a structured, test-oriented, user-space verification module.

## 2. Main Added Functional Modules

The newly added code is divided into two independent functional groups.

### Group A: Process / System Information / Time Interfaces

This group tests process and time related interfaces:

- `uname`
- `gettid`
- `getpid`
- `getppid`
- `clock_gettime`
- `clock_getres`
- `gettimeofday`
- `nanosleep`

These tests verify basic system information retrieval, process-related behavior, time query interfaces, and sleep timing behavior.

### Group B: Memory / File / Output / Signal Interfaces

This group tests memory, file, and signal related interfaces:

- `write`
- `open`
- `read`
- `dup`
- `dup2`
- `mmap`
- `mprotect`
- `signal`
- `alarm`

These tests verify file IO behavior, stdout output, memory mapping behavior, page protection changes, and basic signal delivery behavior.

## 3. Added File Structure

The following files are newly added:

- `apps/libc/c/homework_common.h`
- `apps/libc/c/homework_uname/homework_uname.c`
- `apps/libc/c/homework_gettid/homework_gettid.c`
- `apps/libc/c/homework_pid_ppid/homework_pid_ppid.c`
- `apps/libc/c/homework_clock_gettime/homework_clock_gettime.c`
- `apps/libc/c/homework_clock_getres/homework_clock_getres.c`
- `apps/libc/c/homework_gettimeofday/homework_gettimeofday.c`
- `apps/libc/c/homework_nanosleep/homework_nanosleep.c`
- `apps/libc/c/homework_write_stdout/homework_write_stdout.c`
- `apps/libc/c/homework_open_read/homework_open_read.c`
- `apps/libc/c/homework_dup_dup2/homework_dup_dup2.c`
- `apps/libc/c/homework_mmap_basic/homework_mmap_basic.c`
- `apps/libc/c/homework_mmap_rw/homework_mmap_rw.c`
- `apps/libc/c/homework_mmap_protect/homework_mmap_protect.c`
- `apps/libc/c/homework_signal_basic/homework_signal_basic.c`
- `apps/libc/c/homework_signal_alarm/homework_signal_alarm.c`

The following existing file is updated:

- `apps/libc/testcase_list`

## 4. Design Idea

The implementation uses the existing `apps/libc/c/` mechanism of the repository.

Each test is placed in its own directory and compiled as an independent user-space test program. A common header file `homework_common.h` is added to reduce repeated boilerplate and unify checking logic, assertion helpers, timing conversion helpers, file helpers, and output formatting.

This design improves:

- code organization
- readability
- reusability
- consistency of test output

## 5. Installation and Environment

A typical environment includes:

- Linux or WSL Ubuntu
- the `starry-next` source tree
- the repository-provided `apps/libc` build workflow

If needed, dependency installation can follow the repository baseline instructions. This homework mainly focuses on source-level addition and organization.

## 6. Build Method

The libc user-space tests are placed under `apps/libc/c/`, so they can be managed by the existing libc build path.

Typical build usage:

```bash
make -C apps/libc ARCH=x86_64 TARGET=gnu build_c
