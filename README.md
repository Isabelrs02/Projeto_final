Monitoramento de Qualidade da Água com Raspberry Pi Pico W

Descrição

Este projeto implementa um sistema embarcado para monitoramento de qualidade da água utilizando a Raspberry Pi Pico W. Ele simula a medição de pH, turbidez e temperatura, exibindo os valores ajustáveis por meio de LEDs e gerando alertas com um buzzer quando os parâmetros estão fora dos limites ideais.

Funcionalidades

Simulação de Parâmetros: pH, turbidez e temperatura.

Ajuste Manual: Botões para alterar os valores dos parâmetros.

Indicação por LEDs:

Vermelho: Condição fora dos limites seguros.

Azul: Condição em alerta.

Verde: Dentro dos padrões ideais.


Alerta Sonoro: O buzzer emite um som se os valores estiverem críticos.

Depuração via Serial: Mensagens de status e alterações de parâmetros são exibidas no terminal.


Componentes Utilizados

Raspberry Pi Pico W

LEDs: Vermelho, verde e azul

Buzzer

Botões para seleção e ajuste dos parâmetros

Resistores e fios de conexão


Configuração dos Pinos

Instalação e Execução

Requisitos

SDK da Raspberry Pi Pico configurado no ambiente

CMake e ferramentas de compilação


Compilação e Upload

1. Clone este repositório:

git clone : 


2. Compile o projeto:

mkdir build && cd build
cmake ..
make


3. Envie o firmware para a Pico W:

Conecte a Pico no modo BOOTSEL.

Copie o arquivo .uf2 gerado para a unidade montada.


Execução e Monitoramento

Para visualizar os logs, use um terminal serial:

screen /dev/ttyUSB0 115200

Testes

Pressione Botão A para alternar entre pH, turbidez e temperatura.

Pressione Botão B para aumentar o valor do parâmetro (ele retorna ao mínimo ao ultrapassar o limite).

Verifique a cor do LED correspondente ao estado.

Caso um valor saia dos limites seguros, o buzzer emite um som de alerta.


Melhorias Futuras : 

Integração com Wi-Fi para envio de dados.

Interface gráfica para monitoramento remoto.

Sensores reais para medição dos parâmetros.


Vídeo Demonstrativo

Assista à demonstração do projeto no YouTube: 

Repositório no GitHub :
https://github.com/Isabelrs02/Projeto_final.git

Autor

Projeto desenvolvido por [Isabel Rosa de Santana].



