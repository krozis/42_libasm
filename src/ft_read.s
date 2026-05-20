global ft_read
extern __errno_location     ; external function

section .text
ft_read:                   ; three args -> rdi (fd), rsi (buf), rdx (count)
    mov rax, 0              ; syscall number for write is 1
    syscall                 ; call kernel -> result in rax

    cmp rax, 0              ; rax < 0 ?
    jl .error               ; if yes -> handle error
    ret                     ; else -> just return 

.error:
    mov rbx, rax            ; save the negative errcode
    call __errno_location   ; rax = errno address
    neg rbx;                ; make errcode positive
    mov [rax], ebx          ; write the positive code into errno
                            ; ebx instead of rbx since errno is an int (32bits)
    mov rax, -1             ; return value = -1
    ret                     ; return(rax)
