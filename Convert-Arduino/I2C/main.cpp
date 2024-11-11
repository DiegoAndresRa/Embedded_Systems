#include <iostream>
#include <wiringPiI2C.h>
#include <fstream>
#include <unistd.h>
#include <ctime>
#include <string>
#include <iomanip>
#include <sstream>
#include <chrono>

using namespace std;
#define DEVICE_ID 0x08

int main (int argc, char **argv){
    // Setup I2C communication
    int fd = wiringPiI2CSetup(DEVICE_ID);
    if (fd == -1) {
        cout << "Failed to init I2C communication.\n";
        return 1;
    }
    cout << "I2C communication successfully setup.\n";
    
    // Setup to write within
    ofstream data("amplitudes.txt");
    ofstream times("times.txt");
    if(!data || !times){
        cout << "Error: Unable to open the file. " << endl;
        return 1;
    }
    
    // Comunication process
    int received_data, count = 0;
    timespec ts;

    while(count < 1000){
        // Toma de tiempo inicial
        auto begin = chrono::high_resolution_clock::now();
        // Read data from arduino
        received_data = wiringPiI2CRead(fd);
        // Toma de tiempo final
        auto end = chrono::high_resolution_clock::now();
        // Calcular el tiempo transcurrido en nanosegundos
        auto elapsed = chrono::duration_cast<chrono::nanoseconds>(end - begin).count();
        // Write data
        data << "" << received_data << endl;
        count ++;
        // Write time
        times << elapsed << endl;
    }
    data.close();
    times.close();

    return 0;
}
