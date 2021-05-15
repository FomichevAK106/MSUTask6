section .data
    const1 dq 3.0
    const2 dq 2.0

section .text
GLOBAL f1
GLOBAL f2
GLOBAL f3

f1:
    push ebp
    mov ebp, esp

    finit
    ; st0 == x
    fld qword [ebp + 8]

    ; st0 = e ^ (-x)
    fldl2e
    fmulp st1, st0;
    fld1
    fld st1
    fprem
    f2xm1
    faddp st1, st0
    fscale
    fstp st1
    fld1
    fdivrp

    ; st0 += 3.0
    fadd qword [const1]

    pop ebp
    ret
f2:
    push ebp
    mov ebp, esp
    
    finit
    ; st0 == x
    fld qword [ebp + 8]; st(0) == x

    ; st0 = e ^ (-x)
    fmul qword [const2]

    ; st0 = st0 - 3.0
    fsub qword [const2]

    pop ebp
    ret
f3:
    push ebp
    mov ebp, esp
    
    finit
    ; st0 == 1/x
    fld qword [ebp + 8]; st(0) == x
    fld1
    fdivr

    pop ebp
    ret
