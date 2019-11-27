[BITS 64]

global syscall
syscall:
    push rsp
    push rbp
    
    push rbx
    push r12
    push r13
    push r14
    push r15

    mov r12, rdi ; syscall_id
    mov rdi, rsi ; arg0
    mov rsi, rdx ; arg1
    mov rdx, rcx ; arg2
    ;mov r8 , r8  ; arg3
    ;mov r9 , r9  ; arg4

    ;pop r10 ; arg6 ; do this later

    syscall

    pop r15
    pop r14
    pop r13
    pop r12
    pop rbx

    pop rbp
    pop rsp
    
    ret