#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<stdlib.h>
#include<time.h>

int main(int argc, char** argv){
    const char* GPIOS[8] = {"27","22","26","19","6","5","9","10"};

    if(argc <= 1){
        printf("No hay comandos\n");
        printf("los comandos a utilizar es config, valor, cerrar\n");
        return 1;
    }

    if(strcmp(argv[1],"config") == 0){
        char addres[33];
        FILE* exp = fopen("/sys/class/gpio/export","a");
        FILE* dir = NULL;

        if (exp == NULL) {
            fprintf(stdout,"Error al abrir /sys/class/gpio/export");
            return 1;
        }

        for(int i=0;i<8;i++){
            printf("Exporanto GPIO numero %s\n",GPIOS[i]);
            fprintf(exp,"%s",GPIOS[i]);
            fflush(exp); 
            sleep(1);

            strcpy(addres,"/sys/class/gpio/gpio");
            strcat(addres,GPIOS[i]);
            strcat(addres,"/direction");

            dir = fopen(addres,"a");
            fprintf(dir,"in");
            fclose(dir);
        }
        fclose(exp);
    }

    if(strcmp(argv[1],"cerrar") == 0){
        FILE* unexp = fopen("/sys/class/gpio/unexport","a");
        for(int i=0;i<8;i++){
            printf("Cerrando el GPIO %s\n",GPIOS[i]);
            fprintf(unexp,"%s",GPIOS[i]);
        }
        fclose(unexp);
    }

    if(strcmp(argv[1],"valor")){
        struct timespec ts;
        FILE* pin = NULL;
        FILE* amplitudes = NULL;
        FILE* times = NULL;
        char bits[8][29];
        int numero = 0;
        char* amplitud = (char*)calloc(10,sizeof(char));
        char* hhmmss = (char*)calloc(8,sizeof(char));
        char* time = (char*)calloc(20,sizeof(char));

        for(int i=0;i<8;i++)
            snprintf(bits[i],sizeof(bits[i]),"/sys/class/gpio/gpio%s/value",GPIOS[i]);

        for(int i=0;i<100;i++){
            amplitudes = fopen("c_amplitudes.txt","w");
            times = fopen("c_times.txt","w");
            // get number
            for(int i=0;i<8;i++){
                pin = fopen(bits[i],"r");
                fscanf(pin,"%s",amplitud);
                fclose(pin);
                numero += atoi(amplitud);
            }
            // get time
            clock_gettime(CLOCK_REALTIME, &ts);
            strftime(hhmmss, 8, "%T", localtime(&ts.tv_sec));
            snprintf(time,20,"%s:%09ld", hhmmss, ts.tv_nsec);
            
            fprintf(times,"%s",time);
            fprintf(amplitudes,"%d",numero);
        } 
        fclose(amplitudes);
        fclose(times);
        free(amplitud); 
        free(time); 
        free(hhmmss); 
    }
}