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
        // Read data from arduino
        received_data = wiringPiI2CRead(fd);
        
        // getting time
        clock_gettime(CLOCK_REALTIME, &ts);
        char hhmmss[9];
        strftime(hhmmss, sizeof(hhmmss), "%X", localtime(&ts.tv_sec));
	    usleep(500);
        std::ostringstream oss;
        oss << hhmmss << ":" << std::setw(9) << std::setfill('0') << ts.tv_nsec;
        std::string time = oss.str();
        
        // Write data
        times << time << endl;
        
        // Write data
        data << "" << received_data << endl;
        count ++;
    }
    data.close();
    times.close();

    return 0;
}
