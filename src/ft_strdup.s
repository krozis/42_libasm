global ft_strdup

extern malloc
extern ft_strlen

section .text
ft_strdup:                      ; one arg -> rdi (s)
    push rbx                    ; save rbx and align stack (rsp) for calls
    mov rbx, rdi                ; save s before any call

    call ft_strlen wrt ..plt    ; rax = ft_strlen(s)  /  after a call, rsp is exactly where it was before, so no need to push anything now
    inc rax                     ; rax +=1 (for the final '\0')
    mov rdi, rax                ; malloc argument rdi = size
    call malloc wrt ..plt       ; rax = allocated pointer / use PRT too look for mallocs address

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
    pop rbx                     ; restore rbx
    ret                         ; return allocated pointer or NULL

section .note.GNU-stack noalloc noexec nowrite progbits
