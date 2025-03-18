.section .text
.align 2
.globl setupUART
#include "memoryMap.inc"
#include "UART.inc"
setupUART:
 addi sp, sp, -16
 # allocate a stack frame, moves the stack up by 16 bits
 sw ra, 12(sp)

 li t0, UART_CTRL_ADDR # load UART base address
 li t1, 0x01
 # 0s bit set to 1 for transmit/receive enable, 1st bit set to 0 for 1 stop bit
 sw t1, UART_txctrl(t0)
 # load desired parameters into the txctrl mem location
 sw t1, UART_rxctrl(t0)
 # load desired parameters into the rxctrl mem location
 lw ra, 12(sp) # return the return address
 addi sp, sp, 16 # deallocate the stack
 ret