#include<iostream>
#include<string>
#include<unistd.h>
#include<stdio.h>
#include<chrono>
#include<string.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<fstream>

using namespace std;

int main(int arge , char *argv[]){
    int socket_desc, new_socket, c, read_size; 
    struct sockaddr_in server, client;
    char client_message[3];

    //Create socket
    socket_desc = socket (AF_INET, SOCK_STREAM, 0);
    if (socket_desc == -1) printf("Could not create socket");

    //Prepare the sockaddr in structure
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons ( 5050 );

    if (bind(socket_desc, (struct sockaddr *)&server , sizeof(server)) < 0){
        puts("bind failed");
        return 1;
    }
    puts("bind done");
    listen(socket_desc, 3);

    //Accept and incoming connection
    puts("Waiting for incoming connections...");
    c = sizeof (struct sockaddr_in);
    new_socket = accept(socket_desc, (struct sockaddr *)&client, (socklen_t*)&c);
    
    if (new_socket<0){
        perror ("accept failed");
        return 1;
    }

    puts("Connection accepted");
    // Abriendo el archivo de salida
    ofstream myfile;
    myfile.open("socketsOut.txt");

    while (1){
        auto begin = chrono::high_resolution_clock:: now();
        read_size = recv(new_socket, client_message , 3, 0);
        // Toma de tiempo final
        auto end = chrono::high_resolution_clock::now();
        auto elapsed = chrono::duration_cast<chrono:: nanoseconds>(end - begin) .count();
        
        myfile << "TIEMPO: " << elapsed << "|| ADC Valor: " << client_message << "In";
        
        if(read_size <= 0)
            break;
    }

    if (read_size == 0){
        puts("Client disconnected");
        fflush (stdout);
    }else if(read_size == -1){
        perror ("recv failed");
    }
    close (socket_desc);
    return 0;
}