#pragma once

#include <asm/unistd.h>

#if defined(__x86_64__)

static long syscall5(long number, long a, long b, long c, long d, long e) {
    register long r10 __asm__("r10") = d;
    register long r8 __asm__("r8") = e;
    long result;
    __asm__ volatile("syscall"
                     : "=a"(result)
                     : "a"(number), "D"(a), "S"(b), "d"(c), "r"(r10), "r"(r8)
                     : "rcx", "r11", "memory");
    return result;
}

// The kernel enters _start with a 16-byte aligned stack, but C functions expect it to be off by 8 (the return address).
#define ENTRY_POINT __attribute__((noreturn, force_align_arg_pointer))

#elif defined(__aarch64__)

static long syscall5(long number, long a, long b, long c, long d, long e) {
    register long x8 __asm__("x8") = number;
    register long x0 __asm__("x0") = a;
    register long x1 __asm__("x1") = b;
    register long x2 __asm__("x2") = c;
    register long x3 __asm__("x3") = d;
    register long x4 __asm__("x4") = e;
    __asm__ volatile("svc 0"
                     : "+r"(x0)
                     : "r"(x8), "r"(x1), "r"(x2), "r"(x3), "r"(x4)
                     : "memory");
    return x0;
}

#define ENTRY_POINT __attribute__((noreturn))

#else
#error "Unsupported architecture: only x86_64 and aarch64 are implemented"
#endif

static long syscall3(long number, long a, long b, long c) {
    return syscall5(number, a, b, c, 0, 0);
}
