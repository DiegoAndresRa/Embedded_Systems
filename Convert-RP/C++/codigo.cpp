#include <iostream>
#include <fstream>
#include <string>
#include <unistd.h>
#include <cstdlib>
#include <ctime>
#include <vector>

using namespace std;

int main(int argc, char** argv) {
    vector<string> GPIOS = {"26", "19", "6", "5", "9", "10", "22", "27"};

    if (argc <= 1) {
        cout << "No hay comandos" << endl;
        cout << "Los comandos a utilizar son: config, valor, cerrar" << endl;
        return 1;
    }

    if (string(argv[1]) == "config") {
        string address;
        ofstream exp("/sys/class/gpio/export");
        if (!exp.is_open()) {
            cerr << "Error al abrir /sys/class/gpio/export" << endl;
            return 1;
        }

        for (const auto& gpio : GPIOS) {
            cout << "Exportando GPIO número " << gpio << endl;
            exp << gpio;
            exp.flush();
            sleep(1);

            address = "/sys/class/gpio/gpio" + gpio + "/direction";
            ofstream dir(address);
            if (dir.is_open()) {
                dir << "in";
                dir.close();
            } else {
                cerr << "Error al abrir " << address << endl;
            }
        }
        exp.close();
    } 
    else if (string(argv[1]) == "cerrar") {
        ofstream unexp("/sys/class/gpio/unexport");
        if (!unexp.is_open()) {
            cerr << "Error al abrir /sys/class/gpio/unexport" << endl;
            return 1;
        }

        for (const auto& gpio : GPIOS) {
            cout << "Cerrando el GPIO " << gpio << endl;
            unexp << gpio;
        }
        unexp.close();
    } 
    else if (string(argv[1]) == "valor") {
        struct timespec ts;
        ifstream pin;
        ofstream amplitudes, times;
        vector<string> bits(8);
        int numero = 0;
        string amplitud, hhmmss, time_str;

        for (size_t i = 0; i < GPIOS.size(); ++i) {
            bits[i] = "/sys/class/gpio/gpio" + GPIOS[i] + "/value";
        }

        for (int i = 0; i < 100; ++i) {
            numero = 0;
            amplitudes.open("amplitudes.txt", ios::app);
            times.open("times.txt", ios::app);
            usleep(100000); // Pausa de 100ms

            for (size_t i = 0; i < GPIOS.size(); ++i) {
                pin.open(bits[i]);
                if (pin.is_open()) {
                    pin >> amplitud;
                    pin.close();
                    numero += stoi(amplitud);
                } else {
                    cerr << "Error al abrir " << bits[i] << endl;
                }
            }

            // Obtener tiempo
            clock_gettime(CLOCK_REALTIME, &ts);
            char buffer[9];
            strftime(buffer, 9, "%X", localtime(&ts.tv_sec));
            hhmmss = string(buffer);
            time_str = hhmmss + ":" + to_string(ts.tv_nsec).substr(0, 9);

            times << time_str << endl;
            amplitudes << numero << endl;

            amplitudes.close();
            times.close();
        }
    } 
    else {
        cerr << "Comando no reconocido" << endl;
        return 1;
    }

    return 0;
}

