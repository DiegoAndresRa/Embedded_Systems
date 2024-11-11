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
  valor = 0;
  for(i=0; i<=7; i++){
    int valori= digitalRead(pines[i]);
    valor += valori;
  }
}

// SPI interrupt routine
ISR (SPI_STC_vect){
  SPDR = valor;
} 




