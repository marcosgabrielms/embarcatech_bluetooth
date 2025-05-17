#include "bluetooth.h"
#include "hardware/uart.h"
#include "hardware/gpio.h"

#define UART_ID uart1
#define BAUD_RATE 9600
#define UART_TX_PIN 18  // GP4 → RX do HC-05
#define UART_RX_PIN 19  // GP8 ← TX do HC-05

void bluetooth_init(void) {
    uart_init(UART_ID, BAUD_RATE);
    gpio_set_function(UART_TX_PIN, GPIO_FUNC_UART);
    gpio_set_function(UART_RX_PIN, GPIO_FUNC_UART);
    gpio_pull_up(UART_RX_PIN);
}

bool bluetooth_available(void) {
    return uart_is_readable(UART_ID);
}

char bluetooth_read_char(void) {
    return uart_getc(UART_ID);
}
