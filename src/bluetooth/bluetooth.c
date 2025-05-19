#include "bluetooth.h"


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

void bluetooth_read_string(uart_inst_t *uart, char *buffer, size_t max_len) {
    size_t i = 0;

    while (i < max_len - 1) {
        // Espera até receber um caractere
        char c = uart_getc(uart);

        // Se for Enter (\r ou \n), encerra a string
        if (c == '\r' || c == '\n') {
            break;
        }

        buffer[i++] = c;
    }

    buffer[i] = '\0'; // Termina a string
}