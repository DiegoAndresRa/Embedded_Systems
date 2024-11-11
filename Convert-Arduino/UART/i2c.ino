#include <Wire.h>

int i, valor = 0;
const int pines[8] = {2, 3, 4, 5, 6, 7 ,8, 9}; 

void setup() {
  // Setup Serial Comunication
  Serial.begin(9600);
  for(i = 0; i<= 7; i++){ pinMode(pines[i], INPUT); } 
}

void loop() {
  valor = 0;
  for(i=0; i<=7; i++){
    int valori= digitalRead(pines[i]);
    valor += valori;
  }
  Serial.println(valor);
  delay(1000);
}
