global ft_strdup

extern malloc
extern ft_strlen

section .text
ft_strdup:                      ; one arg -> rdi (s)
    mov rbx, rdi                ; save s before any call

    call ft_strlen              ; rax = ft_strlen(s)
    inc rax                     ; rax +=1 (for the final '\0')
    mov rdi, rax                ; malloc argument rdi = size
    call malloc                 ; rax = allocated pointer

    cmp rax, 0                  ; did malloc failed? (rax == 0)
    je .done                    ; goto .done to return NULL

    mov rcx, rax                ; save dest pointer (rax will be our return value)

.copy:                          ; now rbx == src and rcx == destination
    mov dl, [rbx]               ; load byte from src
    mov [rcx], dl               ; write byte to dest
    cmp dl, 0                   ; is it end of string ?
    je .done                    ; if yes, goto .done
    inc rbx                     ; src++
    inc rcx                     ; dest++
    jmp .copy                   ; goto .copy loop

.done:
    ret                         ; return allocated pointer or NULL
                                                  