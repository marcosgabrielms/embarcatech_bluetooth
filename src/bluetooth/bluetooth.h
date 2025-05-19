#ifndef BLUETOOTH_H
#define BLUETOOTH_H

#include "hardware/uart.h"
#include "hardware/gpio.h"
#include <stdbool.h>

#define UART_ID uart1
#define BAUD_RATE 9600
#define UART_TX_PIN 18  // GP4 → RX do HC-05
#define UART_RX_PIN 19  // GP8 ← TX do HC-05


// Inicializa a UART para comunicação com o módulo HC-05
void bluetooth_init(void);

// Retorna true se há dados disponíveis para leitura
bool bluetooth_available(void);

// Lê um caractere da UART Bluetooth
char bluetooth_read_char(void);

void bluetooth_read_string(uart_inst_t *uart, char *buffer, size_t max_len);

#endif // BLUETOOTH_H
