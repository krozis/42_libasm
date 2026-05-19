global ft_strlen            ; make function ft_strlen visible from outside

section .text
ft_strlen:
    mov     rax, 0          ; set rax (return value / counter) to zero

.loop:
    cmp byte [rdi+rax], 0   ; rdi[rax] == 0 ? (if yes, set ZF (Zero Flag) to 1)
    je .done                ; if ZF, go to .done
    inc rax                 ; rax++
    jmp .loop               ; jump to .loop

.done:
    ret                     ; return(rax)
