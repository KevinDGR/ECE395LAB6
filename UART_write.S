.section .text
.align 2
.globl UART_write
#include "memoryMap.inc"
#include "UART.inc"
UART_write:
 addi sp, sp, -16
 # allocate a stack frame, moves the stack up by 16 bits
 sw ra, 12(sp)

 li t0, UART_CTRL_ADDR # load base address for UART
 loop:
 lw t1, UART_txdata(t0) # load rxdata register
 li t2, 0x80000000 # create mask for rxdata to isolate empty bit
 and t3, t2, t1
 # AND the rxdata mask and register to see if empty bit is set
 bnez t3, loop
 
 sb a0, UART_txdata(t0)

 lw ra, 12(sp) # load the return address
 addi sp, sp, 16 # deallocate the stack
 ret