section .text
global julia_set

julia_set:
    push rbp
    mov rbp, rsp

epilog:
    mov rsp, rbp
    pop rbp
    ret