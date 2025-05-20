#include "bluetooth.h"  // Inclui o cabeçalho com as definições da interface Bluetooth

// Inicializa a UART para comunicação com o módulo Bluetooth
void bluetooth_init(void) {
    uart_init(UART_ID, BAUD_RATE); // Inicializa a UART com o ID e a taxa de transmissão definida
    gpio_set_function(UART_TX_PIN, GPIO_FUNC_UART); // Configura o pino TX para função UART
    gpio_set_function(UART_RX_PIN, GPIO_FUNC_UART); // Configura o pino RX para função UART
    gpio_pull_up(UART_RX_PIN); // Ativa o pull-up no pino RX para evitar flutuações
}

// Verifica se há dados disponíveis para leitura via Bluetooth
bool bluetooth_available(void) {
    return uart_is_readable(UART_ID); // Retorna true se houver dados na UART
}

// Lê um caractere da UART (Bluetooth)
char bluetooth_read_char(void) {
    return uart_getc(UART_ID); // Lê e retorna um caractere recebido via UART
}

// Lê uma string completa da UART até Enter ou atingir o tamanho máximo
void bluetooth_read_string(uart_inst_t *uart, char *buffer, size_t max_len) {
    size_t i = 0;

    while (i < max_len - 1) {
        // Espera até receber um caractere da UART
        char c = uart_getc(uart);

        // Se o caractere for Enter (carriage return '\r' ou newline '\n'), encerra a leitura
        if (c == '\r' || c == '\n') {
            break;
        }

        buffer[i++] = c; // Armazena o caractere no buffer
    }

    buffer[i] = '\0'; // Adiciona o caractere nulo para finalizar a string corretamente
}
