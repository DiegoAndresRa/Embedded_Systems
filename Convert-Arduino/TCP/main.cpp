#include<iostream>
#include<wiringPiI2C.h>
#include<string>
#include<unistd.h>
#include<stdio.h>
#include<string.h>
#include<sys/socket.h>
#include<arpa/inet.h>

using namespace std;
#define DEVICE_ID 0x08

int main(int argc, char* argv[]){
    int socket_desc;
    struct sockaddr_in server;
    const char *message;

    //Create socket
    socket_desc = socket (AF_INET , SOCK_STREAM , 0) ;
    if (socket_desc == -1) printf("Could not create socket");

    server.sin_addr.s_addr = inet_addr("192.168.0.106");
    server.sin_family = AF_INET;
    server.sin_port = htons (5050);

    //Connect to remote server
    if (connect(socket_desc, (struct sockaddr *)&server, sizeof (server)) < 0){
        puts("connect error");
        return 1;
    }
    puts("Connected \n");
    int fd = wiringPiI2CSetup(DEVICE_ID);
    if (fd == -1) {
        std::cout << "Failed to init I2C communication. \n";
        return -1;
    }
    std::cout << "I2C communication successfully setup.\n";

    int received_data, i = 0;
    while (i<1000){

        received_data = wiringPiI2CRead(fd);
        std::string s = std::to_string(received_data);
        message = s.c_str();

        if (send(socket_desc, message, strlen(message) , 0) < 0){
            puts("Send failed");
            return 1;
        } 
        i++;
        usleep (1000);
    }
        close (socket_desc);
        return 0;
    
}
