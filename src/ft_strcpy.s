global ft_strcpy        ; make function ft_strcpy visible from outside



section .text
ft_strcpy:              ; Two arguments (dest in rdi, src in rsi)
    mov rax, rdi        ; save rdi (dest) into rax to return it later

.loop:
    mov cl, [rsi]       ; copy src[] value to tmp 8bits cl
    mov [rdi], cl       ; copy cl value to dest[]
    cmp cl, 0           ; check for '\0'
    je .done            ; if end of string, goto .done
    inc rdi             ; increment rdi
    inc rsi             ; increment rsi
    jmp .loop           ; goto .loop

.done:
    ret                 ; return rax

section .note.GNU-stack noalloc noexec nowrite progbits