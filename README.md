# Controle de LEDs com Botão - Raspberry Pi Pico

Este projeto utiliza o **Raspberry Pi Pico** para controlar três LEDs com um botão. Quando o botão é pressionado, os LEDs acendem em sequência, com um intervalo de tempo controlado por um temporizador.

## Funcionalidades

- Acende LEDs sequencialmente com o pressionamento do botão.
- Implementação de **debouncing** para o botão.
- Controle de LEDs com temporizadores configurados para exibir intervalos entre os LEDs.

## Requisitos

### Hardware

- **Raspberry Pi Pico** (ou qualquer placa compatível com o RP2040).
- 3 LEDs.
- 1 Botão.

### Software

- **Pico SDK** configurado.
- Ambiente de desenvolvimento C/C++ configurado (utilizando o **GCC ARM** e **CMake**).

## Diagrama de Conexões

### LEDs:
- LED 1 no pino **GPIO 11**.
- LED 2 no pino **GPIO 12**.
- LED 3 no pino **GPIO 13**.

### Botão:
- Botão conectado ao pino **GPIO 5** (com pull-up interno).

## Como Funciona

1. O código configura os pinos dos LEDs como saídas e o pino do botão como entrada.
2. Quando o botão é pressionado, uma interrupção é gerada e inicia o controle dos LEDs, acendendo-os em sequência.
3. Um **debounce** é aplicado ao botão para evitar múltiplos acionamentos devido a ruídos na entrada.

## Compilação e Upload

### Pré-requisitos

- Instale o **Pico SDK**:  
  - [Guia de instalação do Pico SDK](https://github.com/raspberrypi/pico-sdk)
  
- Instale o **CMake** e o **GCC Toolchain** para ARM.

### Compilação

1. Crie um diretório para a compilação:
    ```bash
    mkdir build
    cd build
    ```

2. Execute o comando CMake:
    ```bash
    cmake ..
    ```

3. Compile o código:
    ```bash
    make
    ```

4. O arquivo binário será gerado. Copie o arquivo `.uf2` para o Raspberry Pi Pico.

### Upload

1. Coloque o **Raspberry Pi Pico** em **modo de inicialização** (pressione o botão BOOTSEL enquanto conecta o Pico via USB).
2. Copie o arquivo `.uf2` para o dispositivo Pico.
