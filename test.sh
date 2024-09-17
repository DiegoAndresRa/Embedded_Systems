#!/bin/bash

# GPIO utilizados para generar numero
GPIO_0=26
GPIO_1=19
GPIO_2=5
GPIO_3=6
GPIO_4=9
GPIO_5=10
GPIO_6=22
GPIO_7=27

# En caso que no se pase algun valor
if [ $# -ne 1 ]; then   # si no hay argumento
  echo "No hay comando"
  echo "los comandos a utilizar es config, valor, cerrar"
  exit 2     # Numero invalido de argumentos
fi

# Configurar GPIO como entradas

if [ "$1" == "config" ]; then
    for numPin in {0..7};do
        eval pin=\$GPIO_$numPin
        echo "Exportando GPIO numero $pin"
        echo $pin >> "/sys/class/gpio/export"
        sleep 1
        echo "in" >> "/sys/class/gpio/gpio$pin/direction"
    done
fi

if [ "$1" == "cerrar" ]; then
    for numPin in {0..7};do
        eval pin=\$GPIO_$numPin
        echo "Cerrando el GPIO $pin"
        echo $pin >> "/sys/class/gpio/unexport"
    done
fi

if [ "$1" == "valor" ]; then
        bit0=$(cat "/sys/class/gpio/gpio$GPIO_0/value")
        bit1=$(cat "/sys/class/gpio/gpio$GPIO_1/value")
        bit2=$(cat "/sys/class/gpio/gpio$GPIO_2/value")
        bit3=$(cat "/sys/class/gpio/gpio$GPIO_3/value")
        bit4=$(cat "/sys/class/gpio/gpio$GPIO_4/value")
        bit5=$(cat "/sys/class/gpio/gpio$GPIO_5/value")
        bit6=$(cat "/sys/class/gpio/gpio$GPIO_6/value")
        bit7=$(cat "/sys/class/gpio/gpio$GPIO_7/value")
        let numero=bit0+bit1+bit2+bit3+bit4+bit5+bit6+bit7
        for num in {0..7};do
            bit="bit$num"
            echo ${!bit}
        done
        echo $numero
fi