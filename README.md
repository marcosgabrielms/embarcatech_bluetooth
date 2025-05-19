# Embarcatech Bluetooth - Projeto para Raspberry Pi Pico W

## Visão Geral

Este projeto demonstra a comunicação Bluetooth utilizando um Raspberry Pi Pico W e um módulo Bluetooth externo (provavelmente HC-05). O sistema é configurado para receber dados via Bluetooth (UART) e exibi-los no monitor serial. Adicionalmente, o projeto inclui bibliotecas para interação com um display OLED SSD1306, sugerindo a possibilidade de exibir informações em um display externo, embora a integração principal no `embarcatech_bluetooth.c` foque na comunicação serial.

O projeto está configurado para ser desenvolvido e compilado utilizando o SDK do Raspberry Pi Pico, CMake, e pode ser facilmente gerenciado através do Visual Studio Code com as configurações fornecidas.

## Funcionalidades

* **Comunicação Bluetooth:** Estabelece comunicação UART com um módulo Bluetooth para receber dados.
* **Monitoramento Serial:** Exibe os dados recebidos via Bluetooth no monitor serial USB.
* **Suporte a Display OLED (Opcional):** Inclui bibliotecas para controle de um display OLED SSD1306 via I2C, permitindo a exibição de texto e gráficos.
* **Configuração para Raspberry Pi Pico W:** O projeto é especificamente configurado para a placa Pico W.
* **Ambiente de Desenvolvimento VSCode:** Contém configurações para facilitar o desenvolvimento, compilação e depuração no VSCode.

## Requisitos de Hardware

* Raspberry Pi Pico W
* Módulo Bluetooth (ex: HC-05) conectado aos pinos UART definidos (GP16/UART0_TX e GP17/UART0_RX no exemplo principal, ou GP18/UART1_TX e GP19/UART1_RX na biblioteca `bluetooth.c`).
* (Opcional) Display OLED SSD1306 (conectado via I2C).
* Cabos e jumpers para conexões.

## Requisitos de Software e Dependências

* [Raspberry Pi Pico SDK](https://github.com/raspberrypi/pico-sdk) (versão 1.5.1 conforme configurações).
* [ARM GCC Toolchain](https://developer.arm.com/tools-and-software/open-source-software/developer-tools/gnu-toolchain/gnu-rm) (versão 13.2 Rel1 conforme configurações).
* [CMake](https://cmake.org/) (versão 3.13 ou superior).
* [Ninja Build System](https://ninja-build.org/).
* Visual Studio Code (recomendado, com extensões sugeridas em `.vscode/extensions.json`).
    * C/C++ for Visual Studio Code (ms-vscode.cpptools)
    * Cortex-Debug (marus25.cortex-debug)
    * Raspberry Pi Pico/RP2040 (raspberry-pi.raspberry-pi-pico)
    * Serial Monitor (ms-vscode.vscode-serial-monitor)

## Configuração e Compilação

1.  **Clone o repositório:**
    ```bash
    git clone <URL_DO_REPOSITORIO>
    cd embarcatech_bluetooth
    ```

2.  **Configure o Ambiente de Desenvolvimento:**
    * Certifique-se de que o Pico SDK, a toolchain ARM GCC, CMake e Ninja estão instalados e configurados corretamente em seu sistema. Os arquivos em `.vscode/settings.json` tentam configurar os caminhos para essas ferramentas.
    * Se estiver utilizando o VSCode, abra a pasta do projeto. As extensões recomendadas devem ser sugeridas para instalação.

3.  **Crie a Pasta de Build e Configure o CMake:**
    O VSCode com a extensão Raspberry Pi Pico geralmente lida com isso automaticamente. Manualmente, você pode fazer:
    ```bash
    mkdir build
    cd build
    cmake ..
    ```
    O arquivo `CMakeLists.txt` define as fontes, bibliotecas e configurações do projeto.

4.  **Compile o Projeto:**
    No VSCode, utilize a tarefa "Compile Project" (definida em `.vscode/tasks.json`). Manualmente, dentro da pasta `build`:
    ```bash
    ninja
    ```
    Isso gerará os arquivos executáveis (`.uf2`, `.elf`, etc.) dentro da pasta `build`.

## Como Usar/Executar

1.  **Conecte o Hardware:**
    * Conecte o módulo Bluetooth aos pinos UART do Pico W conforme especificado no código (`src/embarcatech_bluetooth.c` usa UART0 nos pinos GP16 e GP17, enquanto `src/bluetooth/bluetooth.c` está configurado para UART1 nos pinos GP18 e GP19. Verifique qual configuração está ativa no `CMakeLists.txt`).
    * Se estiver usando o display OLED, conecte-o aos pinos I2C apropriados.

2.  **Carregue o Firmware:**
    * Coloque o Raspberry Pi Pico W em modo BOOTSEL (pressione o botão BOOTSEL enquanto conecta o cabo USB).
    * Arraste e solte o arquivo `.uf2` (localizado em `build/src/embarcatech_bluetooth.uf2` ou similar) para o drive RPI-RP2 que aparece.
    * Alternativamente, utilize a tarefa "Run Project" ou "Flash" no VSCode, que podem usar `picotool` ou `openocd`.

3.  **Comunicação Bluetooth:**
    * Após carregar o firmware, o Pico W começará a aguardar mensagens via Bluetooth.
    * Pareie seu dispositivo (smartphone, computador) com o módulo Bluetooth (ex: HC-05).
    * Utilize um aplicativo terminal Bluetooth para enviar caracteres ou strings para o Pico W.

4.  **Monitore a Saída:**
    * Abra um monitor serial (através do VSCode Serial Monitor, Arduino IDE, PuTTY, etc.) conectado à porta USB do Pico W.
    * Os caracteres recebidos via Bluetooth serão impressos no monitor serial.

## Estrutura do Diretório
├── .vscode/                  # Configurações do Visual Studio Code (IntelliSense, debug, tasks)
├── build/                    # (Gerado após compilação) Contém os arquivos de build
├── src/
│   ├── bluetooth/
│   │   ├── bluetooth.c       # Implementação da biblioteca de comunicação Bluetooth (para UART1)
│   │   └── bluetooth.h       # Arquivo de cabeçalho para bluetooth.c
│   └── embarcatech_bluetooth.c # Arquivo principal da aplicação (usa UART0, ponto de entrada main())
├── ssd1306/                  # Biblioteca para o display OLED SSD1306
│   ├── font.h                # Definições de fontes para o display
│   ├── ssd1306.c             # Implementação do driver do display SSD1306
│   └── ssd1306.h             # Arquivo de cabeçalho para o driver SSD1306
├── CMakeLists.txt            # Script de configuração do CMake para o projeto
└── lwipopts.h                # Opções de configuração para a pilha LwIP (para Pico W)


Para Desenvolvimentos Futuros,
Integrar Display SSD1306: Adicione código em src/embarcatech_bluetooth.c para inicializar e usar as funções da biblioteca ssd1306/ para exibir informações recebidas ou status.,
Utilizar a Biblioteca src/bluetooth/: Integre ou escolha utilizar as funções de src/bluetooth/bluetooth.c para comunicação via UART1, se necessário.,
Tratamento de Comandos: Implemente uma lógica para processar comandos específicos recebidos via Bluetooth, em vez de apenas ecoar os caracteres.,

Contribuições,
Contribuições são bem-vindas! Sinta-se à vontade para abrir issues ou pull requests.

Licença,
(Defina uma licença, se aplicável. Note que a biblioteca SSD1306 incluída no subdire
