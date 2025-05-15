#include "bluetooth.h"
#include "hardware/uart.h"
#include "pico/stdlib.h"

// UART a ser usada (uart1)
#define BLUETOOTH_UART   uart1
#define BLUETOOTH_BAUDRATE 9600

#define BLUETOOTH_TX_PIN  4  // TX do Pico -> RX do módulo
#define BLUETOOTH_RX_PIN  5  // RX do Pico <- TX do módulo

void bluetooth_init(void) {
    uart_init(BLUETOOTH_UART, BLUETOOTH_BAUDRATE);

    //Configuração dos pinos UART
    gpio_set_function(BLUETOOTH_TX_PIN, GPIO_FUNC_UART);
    gpio_set_function(BLUETOOTH_RX_PIN, GPIO_FUNC_UART);
}

int bluetooth_available(void){
    return uart_is_readable(BLUETOOTH_UART);
}

char bluetooth_read_char(void) {
    return uart_getc(BLUETOOTH_UART);
}


