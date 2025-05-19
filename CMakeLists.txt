# Generated Cmake Pico project file

cmake_minimum_required(VERSION 3.13)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Initialise pico_sdk from installed location
# (note this can come from environment, CMake cache etc)

# == DO NOT EDIT THE FOLLOWING LINES for the Raspberry Pi Pico VS Code Extension to work ==
if(WIN32)
    set(USERHOME $ENV{USERPROFILE})
else()
    set(USERHOME $ENV{HOME})
endif()
set(sdkVersion 1.5.1)
set(toolchainVersion 13_2_Rel1)
set(picotoolVersion 2.0.0)
set(picoVscode ${USERHOME}/.pico-sdk/cmake/pico-vscode.cmake)
if (EXISTS ${picoVscode})
    include(${picoVscode})
endif()
# ====================================================================================
set(PICO_BOARD pico_w CACHE STRING "Board type")

# Pull in Raspberry Pi Pico SDK (must be before project)
include(pico_sdk_import.cmake)

project(embarcatech_bluetooth C CXX ASM)

# Initialise the Raspberry Pi Pico SDK
pico_sdk_init()

# == Executável Principal ==

add_executable(embarcatech_bluetooth 
    src/embarcatech_bluetooth.c
    src/bluetooth/bluetooth.c
    ssd1306/ssd1306.c
    )

pico_set_program_name(embarcatech_bluetooth "embarcatech_bluetooth")
pico_set_program_version(embarcatech_bluetooth "0.1")

# Habilita saída USB como stdio, desativa UART stdio
pico_enable_stdio_uart(embarcatech_bluetooth 0)
pico_enable_stdio_usb(embarcatech_bluetooth 1)

# Includes: adiciona diretórios onde estão os .h
target_include_directories(embarcatech_bluetooth PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}
        ${CMAKE_CURRENT_LIST_DIR}/src
        ${CMAKE_CURRENT_LIST_DIR}/src/bluetooth
        ${CMAKE_CURRENT_LIST_DIR}/ssd1306
    
)

# Bibliotecas necessárias
target_link_libraries(embarcatech_bluetooth 
        pico_stdlib
        hardware_uart
        hardware_i2c
        pico_cyw43_arch_lwip_threadsafe_background
        )

pico_add_extra_outputs(embarcatech_bluetooth)

