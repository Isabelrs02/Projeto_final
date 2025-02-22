cmake_minimum_required(VERSION 3.13)

# Definição dos padrões C e C++
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Definição do board como Pico W
set(PICO_BOARD pico_w CACHE STRING "Board type")

# Configuração específica para a extensão do VS Code para Pico
if(WIN32)
    set(USERHOME $ENV{USERPROFILE})
else()
    set(USERHOME $ENV{HOME})
endif()
set(sdkVersion 2.1.1)
set(toolchainVersion 14_2_Rel1)
set(picotoolVersion 2.1.1)
set(picoVscode ${USERHOME}/.pico-sdk/cmake/pico-vscode.cmake)
if (EXISTS ${picoVscode})
    include(${picoVscode})
endif()

# Importação do Raspberry Pi Pico SDK
include(pico_sdk_import.cmake)

# Nome do projeto
project(Projeto_final C CXX ASM)

# Inicialização do SDK do Pico
pico_sdk_init()

# Adicionando o executável principal
add_executable(Projeto_final Projeto_final.c)

# Definição do nome e versão do programa
pico_set_program_name(Projeto_final "Projeto_final")
pico_set_program_version(Projeto_final "0.1")

# Habilitar saída via UART e USB
pico_enable_stdio_uart(Projeto_final 1)
pico_enable_stdio_usb(Projeto_final 1)

# Adicionando bibliotecas padrão ao projeto
target_link_libraries(Projeto_final pico_stdlib hardware_timer)

# Adicionando diretórios de inclusão
target_include_directories(Projeto_final PRIVATE ${CMAKE_CURRENT_LIST_DIR})

# Gerar arquivos extras de saída
pico_add_extra_outputs(Projeto_final)
