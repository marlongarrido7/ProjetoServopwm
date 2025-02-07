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
6. [Como Executar o Projeto](#como-executar-o-projeto)
7. [Estrutura do Código](#estrutura-do-código)
8. [Trecho de Código](#trecho-de-código)
9. [Referências](#referências)
10. [Demonstração em Vídeo](#demonstração-em-vídeo)

---

## Objetivos
- Implementar um sistema de controle de servomotor utilizando **PWM** no **Raspberry Pi Pico W**.
- Configurar e entender a utilização do **módulo PWM** do microcontrolador **RP2040**.
- Simular o funcionamento do servomotor no ambiente **Wokwi**.
- Desenvolver um sistema que movimente a flange do servomotor suavemente entre **0 e 180 graus**.

---

## Descrição do Projeto
O projeto consiste na implementação de um controle para um **servomotor padrão** utilizando **PWM (Pulse Width Modulation)** no **Raspberry Pi Pico W**. A simulação foi realizada no **Wokwi**, utilizando os seguintes componentes:

1. **Microcontrolador Raspberry Pi Pico W**
2. **Servomotor - Motor Micro Servo Padrão**

O controle do servomotor é realizado através da modulação de largura de pulso (**PWM**) no **GPIO 22**, variando o ciclo de trabalho para definir diferentes posições do servo.

---

## Funcionalidades
- Configuração do **PWM** no **GPIO 22** com frequência de **50Hz** (período de **20ms**).
- Controle do servomotor para posicionamento em **0º, 90º e 180º**.
- Movimentação **suave e contínua** do servomotor entre **0º e 180º**.
- Aguardo de **5 segundos** em cada posição inicial antes da movimentação contínua.

---

## Requisitos do Projeto
1. **Frequência do PWM** no **GPIO 22** configurada para **50Hz** (**20% da nota**).
2. **Ciclo de trabalho do PWM**:
   - **2.400µs (0,12%)** - Servo em **180 graus** (**10% da nota**).
   - **1.470µs (0,0735%)** - Servo em **90 graus** (**10% da nota**).
   - **500µs (0,025%)** - Servo em **0 graus** (**10% da nota**).
3. **Movimentação contínua suave** entre **0º e 180º** com incrementos de **±5µs** e atraso de **10ms** (**35% da nota**).

---

## Diagrama Simplificado de Conexões
```
+--------------------+
| Raspberry Pi Pico W |
|                    |
| GPIO 22 ----------> ServoMotor |
+--------------------+
```

---

## Como Executar o Projeto
1. **Clone** ou **copie** o código-fonte para o seu ambiente local.
2. Configure o ambiente com o **Pico SDK**.
3. Compile e gere o binário:
   ```sh
   mkdir build
   cd build
   cmake ..
   make
   ```
4. **Transfira** o arquivo **.uf2** gerado para o Raspberry Pi Pico W.
5. **Teste** e observe o comportamento do servomotor.

---

## Estrutura do Código
- **servopwm.c** - Contém a lógica para controle do PWM e movimentação do servo.

---

## Trecho de Código
```c
#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/pwm.h"

#define SERVO_PIN 22  // Pino onde o servomotor está conectado

void set_servo_angle(uint slice, uint level) {
    pwm_set_gpio_level(SERVO_PIN, level);
    sleep_ms(5000); // Aguarda 5 segundos
}

int main() {
    stdio_init_all();
    gpio_set_function(SERVO_PIN, GPIO_FUNC_PWM);
    uint slice = pwm_gpio_to_slice_num(SERVO_PIN);
    
    pwm_set_clkdiv(slice, 125.0);
    pwm_set_wrap(slice, 20000);
    pwm_set_enabled(slice, true);
    
    set_servo_angle(slice, 2400);  // 180 graus
    set_servo_angle(slice, 1470);  // 90 graus
    set_servo_angle(slice, 500);   // 0 graus
    
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
}
```

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

