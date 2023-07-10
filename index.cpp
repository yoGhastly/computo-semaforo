#include <RTClib.h>

const int rojo = 11;        // Definimos el valor del pin para el led rojo
const int amarillo = 12;    // Definimos el valor del pin para el led amarillo
const int verde = 13;       // Definimos el valor del pin para el led verd
const int ecoPin = 5;       // Definimos el valor del pin para el eco del sensor de ultrasonido
const int triggerPin = 4;   // Definimos el valor del pin para el disparador (trigger) del sensor de ultrasonido
RTC_DS1307 rtc; // Replace with RTC_DS3231 if using DS3231 module
unsigned long lastDetectionTime = 0; 

void setup() {
  rtc.begin();

  pinMode(verde, OUTPUT);           // Declaramos el pin verde como salida
  pinMode(amarillo, OUTPUT);        // Declaramos el pin amarillo como salida
  pinMode(rojo, OUTPUT);            // Declaramos el pin rojo como salida

  pinMode(triggerPin, OUTPUT);      // Declaramos el pin del disparador como salida
  pinMode(ecoPin, INPUT);           // Declaramos el pin del eco como entrada
}

void loop() {
  DateTime now = rtc.now();
  // Rest of the code...

  int distancia = medirDistancia();

  if (distancia <= 20) {
    // Little car detected, update the last detection time and turn on the green light
    lastDetectionTime = millis();
    digitalWrite(rojo, LOW);      // Turn off red light
    digitalWrite(amarillo, LOW);  // Turn off yellow light
    digitalWrite(verde, HIGH);    // Turn on green light
    delay(10000);                 // Delay for 10 seconds (green light duration)
    digitalWrite(verde, LOW);     // Turn off green light
    digitalWrite(amarillo, HIGH); // Turn on yellow light
    delay(5000);                  // Delay for 3 seconds (yellow light duration)
    digitalWrite(amarillo, LOW);  // Turn off yellow light
    digitalWrite(rojo, HIGH);     // Turn on red light
  } else {
    // No car detected, check if 1 minute has passed since the last detection
     if (millis() - lastDetectionTime >= 30000) {
      digitalWrite(rojo, LOW);    // Turn off red light
      parpadearLuz(amarillo, 500); // Blink yellow light every 500 milliseconds
    }
  }
}

// Helper function to print leading zero for single-digit numbers
void printDigits(int digits) {
  if (digits < 10) {
    Serial.print("0");
  }
  Serial.print(digits);
}

void cambiarLuz(int pin, unsigned long duracion) {
  digitalWrite(pin, HIGH);   // Encender el led en el pin especificado
  delay(duracion);           // Esperar la duración especificada
  digitalWrite(pin, LOW);    // Apagar el led en el pin especificado
  delay(500);                // Esperar 500 milisegundos entre cambios de estado
}

void parpadearLuz(int pin, unsigned long duracion) {
  for (int i = 0; i < 3; i++) {  // Realizar 3 ciclos de parpadeo
    digitalWrite(pin, HIGH);    // Encender el led en el pin especificado
    delay(duracion);            // Esperar la duración especificada
    digitalWrite(pin, LOW);     // Apagar el led en el pin especificado
    delay(duracion);            // Esperar la duración especificada
  }
}

int medirDistancia() {
  digitalWrite(triggerPin, LOW);    // Establecer el pin del disparador en bajo
  delayMicroseconds(2);

  digitalWrite(triggerPin, HIGH);   // Generar pulso de disparo
  delayMicroseconds(10);
  digitalWrite(triggerPin, LOW);

  unsigned long duracion = pulseIn(ecoPin, HIGH);   // Medir la duración del eco
  int distancia = duracion * 0.034 / 2;             // Calcular la distancia en centímetros

  return distancia;
}
