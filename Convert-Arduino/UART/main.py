#!/usr/bin/python3
import time
import serial

def main():
    count = 0

    ser = serial.Serial('/dev/ttyACM0', 9600, timeout=1)
    ser.reset_input_buffer()

    times = open("times.txt", "w")
    amplitudes = open("amplitudes.txt", "w")


    while count < 1000:
        if ser.in_waiting > 0:
            print('.', end='')
            bg = time.time()
            line = ser.readline().rstrip()
            
            if line:
                try:
                    amplitude = float(line.decode('utf-8'))
                    amplitudes.write("{:.8}".format(amplitude) + '\n')
                except ValueError:
                    pass
            else:
                pass

            end = time.time()
            
            t = end-bg
            decimal = t - int(t)
            print(decimal)
            times.write("{:0>10}".format(str(round(decimal, 9))[2:])+'\n')
            count += 1

        ser.reset_input_buffer()

    print()
    times.close()
    amplitudes.close()


if __name__ == '__main__':
    main()