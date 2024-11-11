#include <iostream>
#include <wiringPiSPI.h>

#include <fstream>
#include <unistd.h>
#include <ctime>
#include <string>
#include <iomanip>
#include <sstream>

using namespace std;
#define SPI_CHANNEL 0
#define SPI_CLOCK_SPEED 1000000

int main (int argc, char **argv){
    // Setup SPI communication
    int fd = wiringPiSPISetupMode(SPI_CHANNEL, SPI_CLOCK_SPEED, 0);
    if (fd == -1) {
        std::cout << "Failed to init SPI communication.\n";
        return -1;
    }
    std::cout << "SPI communication successfully setup.\n";
    
    // Setup to write within
    ofstream data("amplitudes.txt");
    ofstream times("times.txt");
    if(!data || !times){
        cout << "Error: Unable to open the file. " << endl;
        return 1;
    }
    
    // Comunication process
    int count = 0;
    unsigned char buf[2] = { 0, 0 };
    timespec ts;

    while(count < 1000){
        // Read data from arduino
        wiringPiSPIDataRW(SPI_CHANNEL, buf, 2);
        // Write data
        data << "" << +buf[1] << endl;
        count ++;
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
    }
    data.close();
    times.close();

    return 0;
}
