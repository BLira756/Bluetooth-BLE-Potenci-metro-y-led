#include <Arduino.h>
#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEServer.h>
#include <BLE2902.h>

// Pines
const int potentiometerPin = 35; // Pin del potenciómetro
const float voltageReference = 3.3; // Voltaje de referencia del ESP32 (3.3V)
const int adcMaxValue = 4095; // Resolución ADC del ESP32
const int ledPin = 32; // Pin del LED

// Definir nombres de servicio y características
#define SERVICE_UUID            "4fafc201-1fb5-459e-8fcc-c5c9c331914b"
#define CHARACTERISTIC_UUID_RX  "beb5483e-36e1-4688-b7f5-ea07361b26a8" // Para recibir comandos
#define CHARACTERISTIC_UUID_TX  "d563b5d5-b0aa-453a-a54e-9a3b9fa8203a" // Para enviar datos del potenciómetro
#define CHARACTERISTIC_UUID_LED "7c7a31b6-91f4-4d82-a72c-926bc4749c57" // Para enviar el estado del LED

BLECharacteristic *pCharacteristicTX;     // Para enviar datos del potenciómetro
BLECharacteristic *pCharacteristicLED;    // Para enviar el estado del LED

float lastVoltage = 0.0; // Guarda el último voltaje enviado
bool ledState = false;   // Estado del LED (apagado por defecto)

// Clase para recibir comandos de BLE (RX)
class MyCallbacks : public BLECharacteristicCallbacks {
  void onWrite(BLECharacteristic *pCharacteristic) {
    std::string rxValue = pCharacteristic->getValue();
    
    if (rxValue.length() > 0) {
      Serial.println("Comando recibido por BLE: " + String(rxValue.c_str()));
      
      if (rxValue == "S" || rxValue == "s") {
        digitalWrite(ledPin, HIGH); // Enciende el LED
        ledState = true;
        Serial.println("LED encendido");

        // Envía el estado del LED ('LED encendido')
        pCharacteristicLED->setValue("LED encendido");
        pCharacteristicLED->notify();
      } else if (rxValue == "N" || rxValue == "n") {
        digitalWrite(ledPin, LOW); // Apaga el LED
        ledState = false;
        Serial.println("LED apagado");

        // Envía el estado del LED ('LED apagado')
        pCharacteristicLED->setValue("LED apagado");
        pCharacteristicLED->notify();
      }
    }
  }
};

void setup() {
  // Inicializa el monitor serial
  Serial.begin(9600);
  pinMode(ledPin, OUTPUT); // Configura el pin del LED como salida
  digitalWrite(ledPin, LOW); // Apaga el LED al inicio

  // Inicializa el dispositivo BLE
  BLEDevice::init("ESP32_BLE");
  BLEServer *pServer = BLEDevice::createServer();

  // Crea el servicio BLE
  BLEService *pService = pServer->createService(SERVICE_UUID);

  // Característica para recibir datos (RX)
  BLECharacteristic *pCharacteristicRX = pService->createCharacteristic(
                                         CHARACTERISTIC_UUID_RX,
                                         BLECharacteristic::PROPERTY_WRITE);
  pCharacteristicRX->setCallbacks(new MyCallbacks());

  // Característica para enviar datos del potenciómetro (TX)
  pCharacteristicTX = pService->createCharacteristic(
                      CHARACTERISTIC_UUID_TX,
                      BLECharacteristic::PROPERTY_NOTIFY);
  pCharacteristicTX->addDescriptor(new BLE2902()); // Agregar descriptor de notificaciones

  // Característica para enviar el estado del LED
  pCharacteristicLED = pService->createCharacteristic(
                       CHARACTERISTIC_UUID_LED,
                       BLECharacteristic::PROPERTY_NOTIFY);
  pCharacteristicLED->addDescriptor(new BLE2902()); // Agregar descriptor de notificaciones

  // Inicia el servicio y comienza a anunciar el dispositivo
  pService->start();
  BLEAdvertising *pAdvertising = BLEDevice::getAdvertising();
  pAdvertising->start();
}

void loop() {
  // Lee el valor del potenciómetro
  int adcValue = analogRead(potentiometerPin);
  float voltage = (adcValue * voltageReference) / adcMaxValue;

  // Condición para encender el LED cuando el voltaje es mayor a 2.1V
  if (voltage > 2.1 && !ledState) {
    digitalWrite(ledPin, HIGH); // Enciende el LED
    ledState = true;
    Serial.println("LED encendido (por voltaje > 2.1V)");

    // Envía notificación del estado del LED ('LED encendido')
    pCharacteristicLED->setValue("LED encendido");
    pCharacteristicLED->notify();
  } else if (voltage <= 2.1 && ledState) {
    digitalWrite(ledPin, LOW); // Apaga el LED
    ledState = false;
    Serial.println("LED apagado (por voltaje <= 2.1V)");

    // Envía notificación del estado del LED ('LED apagado')
    pCharacteristicLED->setValue("LED apagado");
    pCharacteristicLED->notify();
  }

  // Solo notifica si el valor del voltaje ha cambiado significativamente (ej. > 0.01 V)
  if (abs(voltage - lastVoltage) > 0.01) {
    String voltageStr = String(voltage);
    pCharacteristicTX->setValue(voltageStr.c_str());
    pCharacteristicTX->notify(); // Notifica el nuevo valor del potenciómetro

    Serial.print("Valor ADC: ");
    Serial.print(adcValue);
    Serial.print("\tVoltaje: ");
    Serial.print(voltage);
    Serial.println(" V");

    // Actualiza el último voltaje enviado
    lastVoltage = voltage;
  }

  delay(500); // Lee y envía el valor cada 500 ms
}
