global ft_strlen

section .text
ft_strlen:
    mov     rax, 0          ; Compteur = 0
.loop:
    mov     dl, [rdi + rax] ; Charger le caractère à l'adresse (rdi + rax)
    test    dl, dl          ; Est-ce le caractère nul ?
    je      .done           ; Oui -> fin
    inc     rax             ; Sinon, incrémenter le compteur
    jmp     .loop
.done:
    ret
