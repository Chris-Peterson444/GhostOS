.section .text, "ax"
.global SystemCall
SystemCall:
    ecall
    ret

    .end