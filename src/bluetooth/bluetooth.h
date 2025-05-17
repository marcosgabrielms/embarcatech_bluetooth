#ifndef BLUETOOTH_H
#define BLUETOOTH_H

#include <stdbool.h>

// Inicializa a UART para comunicação com o módulo HC-05
void bluetooth_init(void);

// Retorna true se há dados disponíveis para leitura
bool bluetooth_available(void);

// Lê um caractere da UART Bluetooth
char bluetooth_read_char(void);

#endif // BLUETOOTH_H
