
.section .text
.globl _start
_start:
    csrr a0, menvcfg
    csrr a1, mstatus

