#ifndef BLUETOOTH_H //Diretiva de pré-processador em C//
#define BLUETOOTH_H

#include "pico/stdlib.h"

void bluetooth_init(void);
int bluetooth_available(void);
char bluetooth_read_char(void);

#endif
