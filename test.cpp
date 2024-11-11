// Definición de pines de la matriz 7x5 de LEDs
int filas[5] = {2, 3, 4, 5, 6}; // Pines de las filas (solo 5 filas)
int columnas[7] = {7, 8, 9, 10, 11, 12, 13}; // Pines de las columnas (7 columnas)

// Pines de los sensores ultrasónicos
const int triggerPin1 = A0; // Pin de disparo del primer sensor
const int echoPin1 = A1;    // Pin de eco del primer sensor
const int triggerPin2 = A2; // Pin de disparo del segundo sensor
const int echoPin2 = A3;    // Pin de eco del segundo sensor

// Variables para calcular las distancias
long duracion1, duracion2;
int distancia1, distancia2;

// Función para inicializar la matriz de LEDs
void setup() {
  // Configuración de pines de la matriz de LEDs como salida
  for (int i = 0; i < 5; i++) {
    pinMode(filas[i], OUTPUT);
  }
  for (int j = 0; j < 7; j++) {
    pinMode(columnas[j], OUTPUT);
  }

  // Configuración de pines de los sensores ultrasónicos
  pinMode(triggerPin1, OUTPUT);
  pinMode(echoPin1, INPUT);
  pinMode(triggerPin2, OUTPUT);
  pinMode(echoPin2, INPUT);
  
  Serial.begin(9600); // Inicialización de la comunicación serial
}

// Función para leer la distancia de un sensor ultrasónico
int leerDistancia(int triggerPin, int echoPin) {
  digitalWrite(triggerPin, LOW);
  delayMicroseconds(2);
  digitalWrite(triggerPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(triggerPin, LOW);
  
  long duracion = pulseIn(echoPin, HIGH);
  int distancia = duracion * 0.034 / 2; // Conversión a cm
  
  return distancia;
}

// Función para apagar todos los LEDs
void apagarMatriz() {
  for (int i = 0; i < 5; i++) {
    digitalWrite(filas[i], LOW);
    for (int j = 0; j < 7; j++) {
      digitalWrite(columnas[j], HIGH);
    }
  }
}

// Función para encender la fila correspondiente a la distancia detectada
void encenderFila(int fila, int inicioColumna, int finColumna) {
  // Activar la fila específica
  digitalWrite(filas[fila], HIGH);

  // Encender solo las columnas en el rango especificado
  for (int j = inicioColumna; j <= finColumna; j++) {
    digitalWrite(columnas[j], LOW);
  }

  // Apagar la fila después de una breve pausa para evitar parpadeos
  delay(2);
  digitalWrite(filas[fila], LOW);
}

// Función principal
void loop() {
  // Leer distancias de los dos sensores
  distancia1 = leerDistancia(triggerPin1, echoPin1);
  distancia2 = leerDistancia(triggerPin2, echoPin2);

  // Mostrar distancias en el monitor serial
  Serial.print("Distancia 1: ");
  Serial.println(distancia1);
  Serial.print("Distancia 2: ");
  Serial.println(distancia2);

  // Apagar todos los LEDs antes de mostrar el nuevo patrón
  apagarMatriz();

  // Determinar la fila a encender para el sensor 1
  if (distancia1 <= 10) {
    encenderFila(0, 0, 2); // Encender primera fila en columnas 0-2
  } else if (distancia1 <= 20) {
    encenderFila(1, 0, 2); // Encender segunda fila en columnas 0-2
  } else if (distancia1 <= 30) {
    encenderFila(2, 0, 2); // Encender tercera fila en columnas 0-2
  } else if (distancia1 <= 40) {
    encenderFila(3, 0, 2); // Encender cuarta fila en columnas 0-2
  } else if (distancia1 <= 50) {
    encenderFila(4, 0, 2); // Encender quinta fila en columnas 0-2
  }

  // Determinar la fila a encender para el sensor 2
  if (distancia2 <= 10) {
    encenderFila(0, 3, 6); // Encender primera fila en columnas 3-6
  } else if (distancia2 <= 20) {
    encenderFila(1, 3, 6); // Encender segunda fila en columnas 3-6
  } else if (distancia2 <= 30) {
    encenderFila(2, 3, 6); // Encender tercera fila en columnas 3-6
  } else if (distancia2 <= 40) {
    encenderFila(3, 3, 6); // Encender cuarta fila en columnas 3-6
  } else if (distancia2 <= 50) {
    encenderFila(4, 3, 6); // Encender quinta fila en columnas 3-6
  }

  delay(100); // Pequeña pausa antes de la siguiente lectura
}
