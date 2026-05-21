# libasm

A 42 project focused on discovering x86-64 assembly by reimplementing standard C library functions as a static library.

## Overview

The goal is to write each function in NASM assembly (Intel syntax, 64-bit), compile them into a static library `libasm.a`, and link it against a C test program to validate behavior against the originals.

## Constraints

- Intel syntax, not AT&T
- 64-bit only (`.s` files compiled with `nasm -f elf64`)
- No inline ASM — only `.s` files
- `-no-pie` flag is forbidden
- Calling convention (System V AMD64 ABI) must be respected
- Syscall errors must be handled: `errno` must be set correctly

## Build

```bash
make        # builds libasm.a and the test executable
make clean  # removes object files
make fclean # removes everything (objects, library, executable)
make re     # fclean + all
```

Running the test program:
```bash
./libasm
```

> `test_read.txt` must be present in the current directory for the `ft_read` tests.

## Implemented functions

| Function | Description |
|---|---|
| `ft_strlen` | Returns the length of a string |
| `ft_strcpy` | Copies a string into a destination buffer, returns dest |
| `ft_strcmp` | Compares two strings, returns 0 / negative / positive |
| `ft_write` | Wraps the `write` syscall, sets `errno` on error |
| `ft_read` | Wraps the `read` syscall, sets `errno` on error |
| `ft_strdup` | Allocates and returns a copy of a string via `malloc` |

## Key concepts

### Calling convention (System V AMD64 ABI)

Arguments are passed in registers in this order: `rdi`, `rsi`, `rdx`, `rcx`, `r8`, `r9`.
The return value goes in `rax`.

Registers are split into two groups:

| Group | Registers | Rule |
|---|---|---|
| caller-saved | `rax`, `rcx`, `rdx`, `rsi`, `rdi`, `r8`–`r11` | May be freely overwritten |
| callee-saved | `rbx`, `rbp`, `r12`–`r15` | Must be restored before `ret` |

If a function uses a callee-saved register, it must `push` it on entry and `pop` it before returning.

### Stack alignment

The ABI requires `rsp` to be 16-byte aligned just before any `call` instruction.
Since `call` itself pushes 8 bytes (the return address), every function entry starts with `rsp % 16 == 8`.

Any function that calls another function internally must therefore push at least one 8-byte value first to restore alignment. Using `push rbx` achieves both: it saves a callee-saved register and aligns the stack in one instruction.

### Syscall error handling

Syscalls return a negative errno code in `rax` on failure (e.g. `-9` for `EBADF`).
The wrapper must:
1. Detect the negative return value
2. Call `__errno_location` to get the address of `errno`
3. Store the negated error code there
4. Return `-1`

```nasm
syscall
cmp rax, 0
jl  .error
ret

.error:
    push rbx
    mov  rbx, rax
    call __errno_location
    neg  rbx
    mov  [rax], ebx         ; errno is an int (32-bit)
    pop  rbx
    mov  rax, -1
    ret
```
