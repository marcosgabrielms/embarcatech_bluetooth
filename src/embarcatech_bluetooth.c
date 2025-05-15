#include <stdio.h>
#include "pico/stdlib.h"
#include "bluetooth.h"

int main () {
    stdio_init_all();
    bluetooth_init();

    char buffer[64];
    int index = 0;

    printf("Aguardando dados do Bluetooth... \n");

    while(true){
        if (bluetooth_available()) {
            char c = bluetooth_read_char();
           
            printf("%c, c"); // Exibe caractere recebido no monitor serial USB
            
            // Armazena no buffer até '\n' ou limite
            if (c == '\n' || index >= sizeof(buffer) - 1) {
                buffer[index] = '\0';
                printf("\nMensagem recebida: %s\n", buffer);
                index = 0; // reseta buffer
            } else if (c != '\r') {
                buffer[index++] = c;
            }
        }
    }
}