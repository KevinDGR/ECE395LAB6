.equ UART_txdata, 0x00 # transmit data register
.equ UART_rxdata, 0x04 # receive data register
.equ UART_txctrl, 0x08 # transmit control register
.equ UART_rxctrl, 0x0C # receive control register
.equ UART_ie, 0x10 # UART interrupt enable
.equ UART_ip, 0x14 # UART interrupt pending
.equ UART_div, 0x18 # baud rate divisor