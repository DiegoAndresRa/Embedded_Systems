#include <Wire.h>

int valor = 0;
const int pines[8] = {2, 3, 4, 5, 6, 7, 8, 9}; 

void setup() {
  // Configuración de los pines como entrada
  for (int i = 0; i < 8; i++) {
    pinMode(pines[i], INPUT);
  }
  Serial.begin(9600);
}

void loop() {
  valor = digitalRead(2) + digitalRead(3)*2 + digitalRead(4)*4 + digitalRead(5)*8 + digitalRead(6)*16 + digitalRead(7)*32 + digitalRead(8)*64 + digitalRead(9)*128; 
  Serial.println(valor); // Imprimir el valor
}

