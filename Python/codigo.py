import os
import time
from datetime import datetime

GPIOS = ["26","19","6","5","9","10","22","27"]

def export_gpios():
    with open("/sys/class/gpio/export", "a") as exp:
        for gpio in GPIOS:
            print(f"Exportando GPIO número {gpio}")
            exp.write(gpio)
            exp.flush()
            time.sleep(1)
            direction_path = f"/sys/class/gpio/gpio{gpio}/direction"
            with open(direction_path, "w") as dir_file:
                dir_file.write("in")

def unexport_gpios():
    with open("/sys/class/gpio/unexport", "w") as un:
        for gpio in GPIOS:
            print(f"Cerrando el GPIO {gpio}")
            un.write(f"{gpio}")
            un.flush()

def read_values():
    gpio_paths = [f"/sys/class/gpio/gpio{gpio}/value" for gpio in GPIOS]
    amplitudes_file = open("amplitudes.txt", "a")
    times_file = open("times.txt", "a")

    for _ in range(100):
        total_value = 0
        # Lee los valores de los pines GPIO
        for gpio_path in gpio_paths:
            with open(gpio_path, "r") as pin:
                total_value += int(pin.read().strip())

        # Obtén la hora actual con nanosegundos
        now = datetime.now()
        current_time = now.strftime("%H:%M:%S")
        nanoseconds = f"{now.microsecond * 1000:09d}"
        timestamp = f"{current_time}:{nanoseconds}"

        # Guarda en los archivos
        times_file.write(f"{timestamp}\n")
        amplitudes_file.write(f"{total_value}\n")

        time.sleep(0.1)  # Pausa de 100 ms

    amplitudes_file.close()
    times_file.close()

if __name__ == "__main__":
    import sys

    if len(sys.argv) <= 1:
        print("No hay comandos")
        print("Los comandos a utilizar son: config, valor, cerrar")
        sys.exit(1)

    command = sys.argv[1]

    if command == "config":
        export_gpios()
    elif command == "cerrar":
        unexport_gpios()
    elif command == "valor":
        read_values()
    else:
        print("Comando no reconocido")
