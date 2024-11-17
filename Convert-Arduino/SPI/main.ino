#include <SPI.h>

#define SLAVE_ADDRESS 0x08

int i, valor = 0;
const int pines[8] = {2, 3, 4, 5, 6, 7 ,8, 9}; 

void setup() {
  // Setup PINOT
  Serial.begin(9600);
  for(i = 0; i<= 7; i++){ pinMode(pines[i], INPUT); } 

  // SPI
  pinMode(MISO, OUTPUT);
  SPCR |= _BV(SPE);
  SPI.attachInterrupt();
}

void loop() {
  valor = digitalRead(2) + digitalRead(3)*2 + digitalRead(4)*4 + digitalRead(5)*8 + digitalRead(6)*16 + digitalRead(7)*32 + digitalRead(8)*64 + digitalRead(9)*128; 
}

// SPI interrupt routine
ISR (SPI_STC_vect){
  SPDR = valor;
} 




