.section .text
.align 2
.globl UART_read
#include "memoryMap.inc"
#include "UART.inc"
UART_read:
 addi sp, sp, -16
 # allocate a stack frame, moves the stack up by 16 bits
 sw ra, 12(sp)
 li t0, UART_CTRL_ADDR # load base address for UART
 loop:
 lw a0, UART_rxdata(t0) # load rxdata register
 li t1, 0x80000000 # create mask for rxdata to isolate empty bit
 and t3, a0, t1
 # AND the rxdata mask and register to see if empty bit is set
 bnez t3, loop # the data is empty, go back and check again
 # the data is full if the program goes past the branch
 # return will be accomplished via a1 register.
 # (it is the preset return register for RISC-V)
 lw ra, 12(sp)
 addi sp, sp, 16 # deallocate the stack
 ret