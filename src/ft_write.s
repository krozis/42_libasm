global ft_write
extern __errno_location            ; external function

section .text
ft_write:                           ; three args -> rdi (fd), rsi (buf), rdx (count)
    mov rax, 1                      ; syscall number for write is 1
    syscall                         ; call kernel -> result in rax

    cmp rax, 0                      ; rax < 0 ?
    jl .error                       ; if yes -> handle error
    ret                             ; else -> just return

.error:
    push rbx                        ; save rbx and align stack (rsp)
    mov rbx, rax                    ; now we can use rbx -> save the negative errcode
    call __errno_location wrt ..plt ; rax = errno address / use PRT
    neg rbx                         ; make errcode positive
    mov [rax], ebx                  ; write the positive code into errno
                                    ; ebx instead of rbx since errno is an int (32bits)
    pop rbx                         ; restore rbx
    mov rax, -1                     ; return value = -1
    ret                             ; return(rax)

section .note.GNU-stack noalloc noexec nowrite progbits
