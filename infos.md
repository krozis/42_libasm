# Various informations

## STACK

The stack is a zone of memory. `rsp` always holds the address of the top.
It grows **downward**: each `push` subtracts 8 from `rsp`, each `pop` adds 8.

```
Address (example)   |  Content
--------------------|-------------------
0x7fff1240          |  ...
0x7fff1238          |  ...
0x7fff1230  ← rsp   |  top of the stack
0x7fff1228          |  (unused)
```

### What `call` does

`call foo` does two things automatically:
1. Pushes the return address onto the stack (`rsp -= 8`)
2. Jumps to `foo`

The **return address** is where the CPU must go back when it hits `ret`.
`ret` pops it and jumps there.

### Stack alignment

The x86-64 System V ABI requires: **`rsp` must be a multiple of 16 (end in `...0` in hex) just before any `call` instruction.**

Why: modern CPUs have SIMD/SSE instructions that process 16 bytes at once.
These require data to be 16-byte aligned. Functions like `malloc` use them internally.
If the stack is misaligned when they run, the CPU raises an exception → crash.

Since every function is entered via `call` (which pushes 8 bytes), `rsp` always
ends in `...8` at a function's first instruction. That is expected and normal.

```
Caller (rsp = ...0)
  │
  │  call ft_write    → pushes return address, rsp becomes ...8
  ▼
ft_write entry: rsp = ...8     ← always, unavoidable
```

Because hex digits go 0–F, subtracting 8 only ever alternates between `...0` and `...8`.
So each `push`/`pop` toggles the alignment state.

### Fixing alignment before an inner call

If ft_write itself needs to call another function (e.g. `__errno_location`),
it must bring `rsp` back to `...0` first.
One `push` of any 8-byte register does the job:

```
ft_write entry:  rsp = ...8
push rbx      →  rsp = ...0   ✓ ready to call
call __errno_location
  └─ pushes return address  →  rsp = ...8 inside __errno_location  ✓
  └─ ret  →  rsp = ...0
pop rbx       →  rsp = ...8
ret           →  rsp = ...0   caller gets its rsp back intact ✓
```

---

## CALLING CONVENTION — callee-saved registers

Registers are shared between all functions. The ABI splits them into two groups:

| Group          | Registers                          | Rule                                      |
|----------------|------------------------------------|-------------------------------------------|
| caller-saved   | rax, rcx, rdx, rsi, rdi, r8–r11    | May be overwritten by any function freely |
| callee-saved   | rbx, rbp, r12–r15                  | Must be restored before returning         |

**Callee-saved** means: if *you* use one of these registers in your function,
you are responsible for saving its original value and restoring it before `ret`.
The caller trusts these registers to be unchanged after your function returns.

The canonical way is `push` on entry, `pop` before `ret`:

```nasm
my_function:
    push rbx        ; save rbx (it belonged to the caller)
    mov rbx, rdi    ; now free to use rbx
    ; ... do stuff ...
    pop rbx         ; restore rbx for the caller
    ret
```

If you skip this, the caller may silently read a corrupted value from rbx
with no warning or error — undefined behavior.

### The double benefit of `push rbx`

In functions like ft_write (error path) or ft_strdup:
- You need to save a value across a `call` (so a register is needed)
- You need to align the stack before that `call`

`push rbx` solves both at once:
1. Saves the callee-saved register → ABI respected
2. Subtracts 8 from rsp → stack aligned to 16

---

## SYSCALLS vs function calls

Syscalls (`syscall` instruction) do **not** follow the calling convention.
They have their own register mapping and do not touch `rsp`.
No alignment needed before `syscall`.

| Purpose   | Instruction | Return value | Error         |
|-----------|-------------|--------------|---------------|
| C call    | `call`      | rax          | depends on fn |
| Syscall   | `syscall`   | rax          | negative rax  |

On error, syscalls return a **negative errno code** in rax (e.g. `-9` for EBADF).
You must negate it and store it in `errno` manually, then return `-1`.

```nasm
syscall
cmp rax, 0
jl .error
ret

.error:
    push rbx                ; align stack + save rbx
    mov rbx, rax            ; save negative error code
    call __errno_location   ; returns address of errno in rax
    neg rbx                 ; make it positive
    mov [rax], ebx          ; write into errno (int = 32 bits → ebx)
    pop rbx                 ; restore rbx
    mov rax, -1
    ret
