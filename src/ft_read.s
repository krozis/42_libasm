global ft_read
extern __errno_location

section .text
ft_read:                            ; three args -> rdi (fd), rsi (buf), rdx (count)
    mov rax, 0                      ; syscall number for read is 0
    syscall                         ; call kernel -> result in rax

    cmp rax, 0                      ; rax < 0 ?
    jl .error                       ; if yes -> handle error
    ret                             ; else -> just return

.error:
    push rbx                        ; save rbx and align stack (rsp)
    mov rbx, rax                    ; save the negative errcode
    call __errno_location wrt ..plt ; rax = errno address
    neg rbx                         ; make errcode positive
    mov [rax], ebx                  ; write the error code into errno
                                    ; ebx instead of rbx since errno is an int (32bits)
    pop rbx                         ; restore rbx
    mov rax, -1                     ; return value = -1
    ret                             ; return(rax)

section .note.GNU-stack noalloc noexec nowrite progbits
