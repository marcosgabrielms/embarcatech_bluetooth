#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/uart.h"
#include "hardware/i2c.h"
#include "ssd1306/ssd1306.h"

#define PORT_I2C i2c1
#define PIN_SDA 14
#define PIN_SCL 15
#define I2C_ADDRESS 0x3C

ssd1306_t display;

#define UART_ID uart0
#define BAUD_RATE 9600

#define UART_TX_PIN 16   // GP16: envia da placa para o módulo 
#define UART_RX_PIN 17   // GP17: recebe do módulo

// Inicializa o I2C
void init_i2c() {
    i2c_init(PORT_I2C, 400 * 1000); // Inicializa o I2C a 400kHz
    gpio_set_function(PIN_SDA, GPIO_FUNC_I2C);
    gpio_set_function(PIN_SCL, GPIO_FUNC_I2C);
    gpio_pull_up(PIN_SDA);
    gpio_pull_up(PIN_SCL);
}

// Inicializa o display
void init_display() {
    if (!ssd1306_init(&display, 128, 64, I2C_ADDRESS, PORT_I2C)) {
        printf("Falha ao inicializar o display\n");
        return;
    }
}

// Escreve uma mensagem no display
void display_message(ssd1306_t *display, uint32_t x_message, uint32_t y_message, uint32_t font_size, const char *message) {
    ssd1306_draw_string(display, x_message, y_message, font_size, message);
}

// Exibe o conteúdo do buffer no display
void display_show(ssd1306_t *display) {
    ssd1306_show(display);
}

// Limpa o display
void display_clear(ssd1306_t *display) {
    ssd1306_clear(display);
}

void uart_get_string(uart_inst_t *uart, char *buffer, size_t max_len) {
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

int main() {
    stdio_init_all();  // Inicializa USB-Serial para monitoramento
    init_i2c();        // Inicializa o I2C
    init_display();    // Inicializa o display

    display_clear(&display); // Limpa o display

    char message_1[20];
    snprintf(message_1, sizeof(message_1), "START BLUETOOTH");
    display_message(&display, 20, 0, 1, message_1); // Exibe mensagem no display
    display_show(&display); // Atualiza o display

    sleep_ms(2000); // Aguarda 2 segundos

    display_clear(&display); // Limpa o display

    // Inicializa a UART (Bluetooth)
    uart_init(UART_ID, BAUD_RATE);
    gpio_set_function(UART_TX_PIN, GPIO_FUNC_UART);
    gpio_set_function(UART_RX_PIN, GPIO_FUNC_UART);

    char message_2[20];
    snprintf(message_2, sizeof(message_2), "STAY MESSAGE");
    display_message(&display, 20, 15, 1, message_2); // Exibe mensagem no display
    display_show(&display); // Atualiza o display

    sleep_ms(2000); // Aguarda 2 segundos

    // Loop principal
    while (true) {

        display_clear(&display); // Limpa o display

        // Verifica se há dados recebidos via Bluetooth
        if (uart_is_readable(UART_ID)) {
            char message[50];
            uart_get_string(UART_ID, message, sizeof(message)); // Lê a string recebida
            display_message(&display, 0, 32, 1, message);
            display_show(&display); // Atualiza o display
            printf("%s", message);  // Exibe no monitor serial
        }
        sleep_ms(5000);

    }

    return 0;
}
