from datetime import datetime
import serial

def main():
    count = 0

    ser = serial.Serial('/dev/ttyACM0', 9600, timeout=1)
    ser.reset_input_buffer()

    times = open("times.txt", "w")
    amplitudes = open("amplitudes.txt", "w")


    while count > 0:
        if ser.in_waiting > 0:
            bg = datetime.now() 
            
            line = ser.readline().decode('utf-8').rstrip()

            end = datetime.now()
            
            amplitudes.write(line)
            times.write(str(bg-end)[9:])
            
            count += 1
            
    
    times.close()
    amplitudes.close()


if __name__ == '__main__':
    main()