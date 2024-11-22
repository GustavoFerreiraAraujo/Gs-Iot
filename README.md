# Gs-Iot
Este projeto utiliza a placa ESP32 e o serviço Thinger.io para monitorar a tensão de um painel solar e o nível de carga das baterias. O objetivo é ajudar a ter o controle da produção de energia e seu uso.

### Video explicando o projeto:
https://youtu.be/VZzlpYxQgCk

# Componentes Utilizados
ESP32: Microcontrolador com capacidade Wi-Fi.
Thinger.io: Plataforma de IoT para monitoramento e controle remoto.
Resistores: Divisores de tensão para leitura das tensões.
47kΩ (R1) e 10kΩ (R2) para a tensão solar.
33kΩ (R1) e 10kΩ (R2) para a tensão da bateria.
Potenciômetro: Para ajustes manuais e testes.

# Funcionamento

## Configuração da Rede e Thinger.io:
O ESP32 se conecta à rede Wi-Fi definida.
As credenciais do Thinger.iosão configuradas para comunicação com a plataforma.

## Leitura de Tensão:
A função readVoltage lê o valor de ADC dos pinos analógicos e converte para a tensão real utilizando divisores de tensão e a resolução do ADC (4095.0).
Divisores de tensão são utilizados para garantir que a tensão lida esteja dentro do intervalo de leitura do ADC do ESP32.

## Monitoramento da Tensão Solar:
Conecta os resistores R1 (47kΩ) e R2 (10kΩ) ao pino 36 do ESP32.
A leitura da tensão solar é enviada para o Thinger.ioe também exibida no monitor serial.

## Monitoramento do Nível de Bateria:
Conecta os resistores R1 (33kΩ) e R2 (10kΩ) ao pino 39 do ESP32.
A leitura da tensão da bateria é convertida para uma porcentagem considerando 12V como 100%.
A porcentagem da carga da bateria é enviada para o Thinger.ioe exibida no monitor serial.

## Leitura do Potenciômetro:
O potenciômetro está conectado ao pino 34 do ESP32.
A leitura do valor analógico é convertida para tensão e enviada para o Thinger.io, além de ser exibida no monitor serial.

## Envio de Dados para o Thinger.io:
No loop principal, a função thing.handle() é chamada a cada segundo para enviar os dados de leitura para a plataforma Thinger.io.