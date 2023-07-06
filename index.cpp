// Definir pines de los LEDs
const int ledRojo = 2;
const int ledAmarillo = 3;
const int ledVerde = 4;

// Definir pines del sensor ultrasónico
const int trigPin = 5;
const int echoPin = 6;

// Definir umbrales de distancia para activar/desactivar los semáforos
const float umbralPaso = 20.0;  // Distancia de seguridad para permitir el paso
const float umbralDetener = 10.0;  // Distancia crítica para detener el tráfico

void setup() {
  // Configurar pines de los LEDs como salidas
  pinMode(ledRojo, OUTPUT);
  pinMode(ledAmarillo, OUTPUT);
  pinMode(ledVerde, OUTPUT);

  // Configurar pines del sensor ultrasónico
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
}

void loop() {
  // Realizar la medición de distancia utilizando el sensor ultrasónico
  long duracion, distancia;
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duracion = pulseIn(echoPin, HIGH);
  distancia = duracion * 0.034 / 2;

  // Controlar el semáforo según la distancia medida
  if (distancia > umbralPaso) {
    // Permitir el paso en un semáforo
    digitalWrite(ledRojo, LOW);
    digitalWrite(ledAmarillo, HIGH);
    digitalWrite(ledVerde, LOW);
  } else if (distancia > umbralDetener) {
    // Detener el tráfico en ambos semáforos
    digitalWrite(ledRojo, HIGH);
    digitalWrite(ledAmarillo, LOW);
    digitalWrite(ledVerde, LOW);
  } else {
    // Detener el tráfico en el semáforo opuesto
    digitalWrite(ledRojo, LOW);
    digitalWrite(ledAmarillo, LOW);
    digitalWrite(ledVerde, HIGH);
  }
}
