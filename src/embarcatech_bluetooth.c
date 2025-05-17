#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/uart.h"

#define UART_ID uart0
#define BAUD_RATE 9600

#define UART_TX_PIN 16   // GP16: envia da placa para o módulo 
#define UART_RX_PIN 17   // GP17: recebe do módulo

int main() {
    stdio_init_all();  // Inicializa USB-Serial para monitoramento

    // Inicializa a UART (Bluetooth)
    uart_init(UART_ID, BAUD_RATE);
    gpio_set_function(UART_TX_PIN, GPIO_FUNC_UART);
    gpio_set_function(UART_RX_PIN, GPIO_FUNC_UART);

    printf("Aguardando mensagem Bluetooth...\n");

    // Loop principal
    while (true) {
        // Verifica se há dados recebidos via Bluetooth
        if (uart_is_readable(UART_ID)) {
            char ch = uart_getc(UART_ID);
            printf("%c", ch);  // Exibe no monitor serial
        }
    }
}
