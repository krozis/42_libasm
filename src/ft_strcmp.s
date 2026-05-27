global ft_strcmp

section .text
ft_strcmp:              ; two args -> rdi (s1) and rsi (s2)
    mov rax, 0          ; init return value to zero

.loop:
    mov cl, [rdi]       ; load byte from s1
    mov dl, [rsi]       ; load byte from s2

    cmp cl, dl          ; check if cl and dl are differents
    jne .done           ; if different -> exit

    cmp cl, 0           ; check if string is finished
    je .done            ; goto .done

    inc rdi
    inc rsi
    jmp .loop


.done:
    movzx rax, cl       ; "move with zero extension" -> make 8bits cl into 64bits unsigned rax
    movzx rcx, dl       ; make 8bits dl into 64 bits unsigned rcx
    sub rax, rcx        ; rax = rax - rcx
    ret                 ; return (rax) -> 0 if identical, neg value if s1 < s2, else pos value

section .note.GNU-stack noalloc noexec nowrite progbits 