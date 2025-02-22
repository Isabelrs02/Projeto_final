#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include <stdio.h>


// Definindo os pinos dos LEDs e do buzzer
#define LED_PIN_RED 13
#define LED_PIN_GREEN 11
#define LED_PIN_BLUE 12
#define BUZZER_PIN 21  // Alterado para pino 21


// Definindo os pinos dos botões
#define BUTTON_PIN_A 5  // Botão A para alternar entre parâmetros
#define BUTTON_PIN_B 6  // Botão B para ajustar o valor do parâmetro


// Definindo os limites dos parâmetros
#define PH_MIN 0
#define PH_MAX 14
#define TURBIDITY_MIN 0
#define TURBIDITY_MAX 100
#define TEMP_MIN 0
#define TEMP_MAX 40


// Variáveis para os parâmetros simulados
int ph = 7;             // pH da água
int turbidity = 0;      // Turbidez da água (0 = limpa, 100 = totalmente turva)
int temperature = 25;   // Temperatura da água em °C
int current_param = 0;  // 0 = pH, 1 = Turbidez, 2 = Temperatura


// Flag para ativação do buzzer
bool buzzer_active = false;


// Função para gerar som no buzzer
void beep() {
    gpio_put(BUZZER_PIN, 1);
    sleep_ms(100);
    gpio_put(BUZZER_PIN, 0);
}


// Função para atualizar a exibição dos LEDs conforme o parâmetro
void update_led_display() {
    bool red_led_activated = false;


    if (current_param == 0) {  // pH
        if (ph < 6) {
            gpio_put(LED_PIN_RED, 1);
            gpio_put(LED_PIN_GREEN, 0);
            gpio_put(LED_PIN_BLUE, 0);
            red_led_activated = true;
        } else if (ph > 8) {
            gpio_put(LED_PIN_RED, 0);
            gpio_put(LED_PIN_GREEN, 0);
            gpio_put(LED_PIN_BLUE, 1);
        } else {
            gpio_put(LED_PIN_RED, 0);
            gpio_put(LED_PIN_GREEN, 1);
            gpio_put(LED_PIN_BLUE, 0);
        }
    } else if (current_param == 1) {  // Turbidez
        if (turbidity > 70) {
            gpio_put(LED_PIN_RED, 1);
            gpio_put(LED_PIN_GREEN, 0);
            gpio_put(LED_PIN_BLUE, 0);
            red_led_activated = true;
        } else {
            gpio_put(LED_PIN_RED, 0);
            gpio_put(LED_PIN_GREEN, 1);
            gpio_put(LED_PIN_BLUE, 0);
        }
    } else if (current_param == 2) {  // Temperatura
        if (temperature > 35) {
            gpio_put(LED_PIN_RED, 1);
            gpio_put(LED_PIN_GREEN, 0);
            gpio_put(LED_PIN_BLUE, 0);
            red_led_activated = true;
        } else if (temperature < 15) {
            gpio_put(LED_PIN_RED, 0);
            gpio_put(LED_PIN_GREEN, 0);
            gpio_put(LED_PIN_BLUE, 1);
        } else {
            gpio_put(LED_PIN_RED, 0);
            gpio_put(LED_PIN_GREEN, 1);
            gpio_put(LED_PIN_BLUE, 0);
        }
    }


    // Atualiza a flag do buzzer em vez de chamá-lo diretamente
    buzzer_active = red_led_activated;
}


// Função para verificar se os parâmetros estão dentro dos limites ideais
bool check_parameters() {
    return (ph >= 6 && ph <= 8) && (turbidity <= 70) && (temperature <= 35);
}


// Função para exibir o feedback de sucesso
void success_feedback() {
    gpio_put(LED_PIN_RED, 0);
    gpio_put(LED_PIN_GREEN, 1);
    gpio_put(LED_PIN_BLUE, 0);


    for (int i = 0; i < 3; i++) {
        beep();
    }
}


int main() {
    // Inicializando os pinos
    gpio_init(LED_PIN_RED);
    gpio_set_dir(LED_PIN_RED, GPIO_OUT);
    gpio_init(LED_PIN_GREEN);
    gpio_set_dir(LED_PIN_GREEN, GPIO_OUT);
    gpio_init(LED_PIN_BLUE);
    gpio_set_dir(LED_PIN_BLUE, GPIO_OUT);
    gpio_init(BUZZER_PIN);
    gpio_set_dir(BUZZER_PIN, GPIO_OUT);
    gpio_init(BUTTON_PIN_A);
    gpio_set_dir(BUTTON_PIN_A, GPIO_IN);
    gpio_pull_up(BUTTON_PIN_A);
    gpio_init(BUTTON_PIN_B);
    gpio_set_dir(BUTTON_PIN_B, GPIO_IN);
    gpio_pull_up(BUTTON_PIN_B);


    // Inicializando a comunicação serial para depuração
    stdio_init_all();


    while (true) {
        // Checando se o botão A foi pressionado (alternar entre parâmetros)
        if (!gpio_get(BUTTON_PIN_A)) {
            printf("Botão A pressionado. Alternando entre parâmetros...\n");
            sleep_ms(200);
            current_param = (current_param + 1) % 3;
        }


        // Checando se o botão B foi pressionado (ajustar o valor do parâmetro)
        if (!gpio_get(BUTTON_PIN_B)) {
            printf("Botão B pressionado. Ajustando o parâmetro atual...\n");
            sleep_ms(200);


            if (current_param == 0) {  // pH
                ph = (ph + 1) > PH_MAX ? PH_MIN : (ph + 1);
                printf("Novo pH: %d\n", ph);
            } else if (current_param == 1) {  // Turbidez
                turbidity = (turbidity + 10) > TURBIDITY_MAX ? TURBIDITY_MIN : (turbidity + 10);
                printf("Nova turbidez: %d\n", turbidity);
            } else if (current_param == 2) {  // Temperatura
                temperature = (temperature + 1) > TEMP_MAX ? TEMP_MIN : (temperature + 1);
                printf("Nova temperatura: %d\n", temperature);
            }
        }


        // Atualizando a exibição dos LEDs
        update_led_display();


        // Se os parâmetros estiverem ideais, exibir feedback de sucesso
        if (check_parameters()) {
            success_feedback();
        } else if (buzzer_active) {
            beep();  // Agora o beep só toca se a flag buzzer_active estiver ativada
        }


        sleep_ms(100);
    }


    return 0;
}


// Fim do arquivo Projeto_final.c feito por: Isabel Rosa De Santana 