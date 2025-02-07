# Uso de Modulação por Largura de Pulso (PWM) no Controle de Servomotor com Raspberry Pi Pico W 2040

## Autor do Projeto:
**Dr. Marlon da Silva Garrido**  
Professor Associado IV (CENAMB - PPGEA)  
Universidade Federal do Vale do São Francisco (UNIVASF)

Este projeto faz parte das atividades do **EMBARCATECH 2024/25**.

---

## Índice
1. [Objetivos](#objetivos)
2. [Descrição do Projeto](#descrição-do-projeto)
3. [Funcionalidades](#funcionalidades)
4. [Requisitos do Projeto](#requisitos-do-projeto)
5. [Diagrama Simplificado de Conexões](#diagrama-simplificado-de-conexões)
6. [Componentes Utilizados](#componentes-utilizados)
7. [Como Executar o Projeto](#como-executar-o-projeto)
8. [Estrutura do Código](#estrutura-do-código)
9. [Explicação Detalhada do Código](#explicação-detalhada-do-código)
10. [Referências](#referências)
11. [Demonstração em Vídeo](#demonstração-em-vídeo)

---

## Objetivos
- Implementar um sistema de controle de servomotor utilizando **PWM** no **Raspberry Pi Pico W**.
- Configurar e entender a utilização do **módulo PWM** do microcontrolador **RP2040**.
- Simular o funcionamento do servomotor no ambiente **Wokwi**.
- Desenvolver um sistema que movimente a flange do servomotor suavemente entre **0 e 180 graus**.
- Explorar a precisão do controle PWM para aplicações em sistemas embarcados.

---

## Descrição do Projeto
O projeto consiste na implementação de um controle para um **servomotor padrão** utilizando **PWM (Pulse Width Modulation)** no **Raspberry Pi Pico W**. A simulação foi realizada no **Wokwi**, utilizando os seguintes componentes:

1. **Microcontrolador Raspberry Pi Pico W**
2. **Servomotor - Motor Micro Servo Padrão**
3. **Fonte de alimentação adequada (3,3V)**
4. **Jumpers para conexão dos componentes**

O controle do servomotor é realizado através da modulação de largura de pulso (**PWM**) no **GPIO 22**, variando o ciclo de trabalho para definir diferentes posições do servo.

---

## Funcionalidades
- Configuração do **PWM** no **GPIO 22** com frequência de **50Hz** (período de **20ms**).
- Controle do servomotor para posicionamento em **0º, 90º e 180º**.
- Movimentação **suave e contínua** do servomotor entre **0º e 180º**.
- Aguardo de **5 segundos** em cada posição inicial antes da movimentação contínua.
- Código otimizado para melhor precisão no controle do servo.

---

## Componentes Utilizados
- **Raspberry Pi Pico W**
- **Servomotor SG90 ou similar**
- **Jumpers para conexão**
- **Fonte de alimentação 3,3V**
- **Placa de prototipagem (opcional)**

---

## Explicação Detalhada do Código

### Bibliotecas Utilizadas
```c
#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/pwm.h"
```
- **stdio.h** → Permite a utilização de funções de entrada e saída padrão (como `printf()`).
- **pico/stdlib.h** → Biblioteca padrão do Raspberry Pi Pico para inicialização de GPIOs e temporização.
- **hardware/pwm.h** → Biblioteca responsável pelo controle do PWM (Pulse Width Modulation), essencial para o controle do servomotor.

### Definição de Pinos
```c
#define SERVO_PIN 22  // Pino onde o servomotor está conectado
```
- Define o **pino GPIO 22** como a saída PWM para controlar o servomotor.

### Função `set_servo_angle()`
```c
void set_servo_angle(uint slice, uint level) {
    pwm_set_gpio_level(SERVO_PIN, level);
    sleep_ms(5000); // Aguarda 5 segundos
}
```
- **Parâmetros:**
  - `slice`: Identificador do canal PWM correspondente ao GPIO utilizado.
  - `level`: Define o tempo em **microssegundos** que o sinal PWM permanecerá em nível alto (HIGH), o que determina o ângulo do servo.
- **O que a função faz?**
  1. Ajusta o nível PWM no **GPIO 22** usando `pwm_set_gpio_level()`, alterando a posição do servomotor.
  2. Aguarda **5 segundos** (`sleep_ms(5000)`) para que o servo mantenha a posição antes de continuar a execução.

### Função `main()`
```c
int main() {
```
- Função **principal** que inicializa os periféricos e executa o controle do servo.

### Inicialização do PWM
```c
stdio_init_all();
gpio_set_function(SERVO_PIN, GPIO_FUNC_PWM);
uint slice = pwm_gpio_to_slice_num(SERVO_PIN);
```
1. **`stdio_init_all();`** → Inicializa a interface de entrada/saída padrão.
2. **`gpio_set_function(SERVO_PIN, GPIO_FUNC_PWM);`** → Configura o **GPIO 22** como saída PWM.
3. **`uint slice = pwm_gpio_to_slice_num(SERVO_PIN);`** → Obtém o número do **slice PWM** correspondente ao GPIO configurado.

### Posicionamento do Servo
```c
set_servo_angle(slice, 2400);  // 180 graus
set_servo_angle(slice, 1470);  // 90 graus
set_servo_angle(slice, 500);   // 0 graus
```
- Define **três posições fixas** para o servo:
  - **180°** → Pulso de **2400 µs**.
  - **90°** → Pulso de **1470 µs**.
  - **0°** → Pulso de **500 µs**.

### Movimentação Suave entre 0° e 180°
```c
while (true) {
    for (uint level = 500; level <= 2400; level += 5) {
        pwm_set_gpio_level(SERVO_PIN, level);
        sleep_ms(10);
    }
    for (uint level = 2400; level >= 500; level -= 5) {
        pwm_set_gpio_level(SERVO_PIN, level);
        sleep_ms(10);
    }
}
```
- **Controla o movimento contínuo do servo** entre **0° e 180°**.

---

## Referências
- [Raspberry Pi Pico SDK](https://datasheets.raspberrypi.com/pico/raspberry-pi-pico-c-sdk.pdf)
- [Documentação do RP2040](https://www.raspberrypi.com/documentation/microcontrollers/rp2040.html)

---

## Demonstração em Vídeo
Para conferir o projeto em funcionamento, acesse:
[Link do Vídeo](#) *(Em breve)*

Se este projeto foi útil para você, **considere deixar uma estrela no repositório GitHub!** 🌟

**Contato:**  
📧 Email: marlon.garrido@univasf.edu.br  
🌐 Site: [UNIVASF](https://www.univasf.edu.br/)

