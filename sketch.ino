#include <ThingerESP32.h>

#define USERNAME "offGustz"
#define DEVICE_ID "Medidor-de-tensao"
#define DEVICE_CREDENTIAL "_cj3V4jlr8Z1V4$D"

#define SSID "Wokwi-GUEST"
#define SSID_PASSWORD ""

const int solarVoltagePin = 36;
const int batteryVoltagePin = 39;
const int potPin = 34; // Pino do potenciômetro (analógico)
const float adcResolution = 4095.0;

// Configuração do Thinger.io
ThingerESP32 thing(USERNAME, DEVICE_ID, DEVICE_CREDENTIAL);

float readVoltage(int pin, float r1, float r2) {
  float adcValue = analogRead(pin);
  float voltage = (adcValue / adcResolution) * 3.3; // Conversão ADC -> tensão
  return voltage * ((r1 + r2) / r2); // Ajusta pelo divisor de tensão
}

void setup() {
  thing.add_wifi(SSID, SSID_PASSWORD);

  Serial.begin(115200);
  Serial.println("Iniciando setup...");

  // Recurso: Tensão Solar
  thing["solar_voltage"] >> [](pson &out) {
    float solarVoltage = readVoltage(solarVoltagePin, 47000.0, 10000.0); // Resistor R1=47k, R2=10k
    out["voltage"] = solarVoltage;
    Serial.print("Tensão Solar: ");
    Serial.print(solarVoltage);
    Serial.println(" V");
  };

  // Recurso: Porcentagem da Bateria
  thing["battery_percentage"] >> [](pson &out) {
    float batteryVoltage = readVoltage(batteryVoltagePin, 33000.0, 10000.0); // Resistor R1=33k, R2=10k
    float batteryPercentage = (batteryVoltage / 12) * 100; // Considerando 4.2V como 100%
    out["percentage"] = batteryPercentage;
    Serial.print("Porcentagem da Carga da Bateria: ");
    Serial.print(batteryPercentage);
    Serial.println(" %");
  };

  // Recurso: Leitura do Potenciômetro
  thing["potentiometer_value"] >> [](pson &out) {
    int potValue = analogRead(potPin); // Lê o valor do potenciômetro
    float potVoltage = (potValue / adcResolution) * 3.3; // Converte para tensão
    out["value"] = potVoltage;
    Serial.print("Valor do Potenciômetro: ");
    Serial.print(potVoltage);
    Serial.println(" V");
  };

  Serial.println("Setup concluído.");
}

void loop() {
  // Enviar dados para o Thinger.io
  thing.handle();
  delay(1000); // Intervalo entre leituras
}
