# Starry-next Homework Supplement

## 1. 项目概述

本次作业基于 `starry-next` 基线仓库完成。

本次新增内容的核心目标是：在现有仓库基础上，补充一个结构清晰、可组织、可展示的用户态测试模块。

## 2. 新增功能模块

本次新增代码分为两类相互独立的功能模块。

### Group A: 进程 / 系统信息 / 时间接口测试

该模块主要测试以下系统调用或相关接口：

- `uname`
- `gettid`
- `getpid`
- `getppid`
- `clock_gettime`
- `clock_getres`
- `gettimeofday`
- `nanosleep`

这一部分主要用于验证：
- 系统基本信息获取是否正常；
- 进程与线程相关接口是否可用；
- 时间读取接口是否可用；
- 睡眠与时间推进逻辑是否正确。

---

### Group B: 内存 / 文件 / 输出 / 信号接口测试

该模块主要测试以下接口：

- `write`
- `open`
- `read`
- `dup`
- `dup2`
- `mmap`
- `mprotect`
- `signal`
- `alarm`

这一部分主要用于验证：

- 标准输出写入行为；
- 文件创建、读取与描述符复制行为；
- 匿名内存映射与读写行为；
- 内存保护属性修改；
- 信号注册、发送与定时信号行为。

---
## 3. 新增文件结构

本次新增了如下文件：
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

同时修改了以下已有文件：
- `apps/libc/testcase_list`

## 4. 设计思路

本次实现遵循仓库现有的 `apps/libc/c/` 测试组织方式。

每个测试程序单独放在一个目录下，编译后作为一个独立的用户态测试程序运行。为了减少重复代码，并统一输出风格、检查逻辑和辅助函数，我新增了一个公共头文件 `homework_common.h`，用于封装基本输出函数；条件检查与结果断言；时间差计算；文件读写辅助；数据填充与校验；通用工具函数。

这种设计的优点是：

- 代码结构更清晰；
- 各测试之间解耦；
- 复用性更好；
- 输出风格统一，便于自动检查和截图展示。

## 5. 环境准备

典型环境包括：

- Linux 或 WSL Ubuntu
- `starry-next` 源码仓库
- 仓库自带的 `apps/libc` 构建流程

如果需要完整运行测试，可参考仓库原有说明完成环境准备。


