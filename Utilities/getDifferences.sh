#!/bin/bash
read_file=""
write_file=""

# Verifica que se pasen exactamente 2 argumentos, 
# de lo contrario muestra un error.
if [[ $# -eq 0 || $# -lt 2 || $# -gt 2 ]];then
    echo "Error"
    echo "Usage: $0 readFile writeFile"
    exit 1
else
    # Asigna el primer y segundo argumento a las variables.
    read_file=$1
    write_file=$2
    
    # Elimina el archivo de salida si ya existe.
    rm $write_file

    echo "Reading from -> $read_file"
    echo "Writting to -> $write_file"
fi

# Lee el archivo de entrada y almacena los registros en un array.
registros=($(cat $read_file))

nano_per_seg=1000000000  # Define el número de nanosegundos por segundo.

# Itera sobre los primeros 99 registros (0 a 98) para calcular 100 diferencias.
for reg in {0..9999};do 
    # Extrae los segundos del registro actual y el siguiente, eliminando ceros 
    # a la izquierda.
    seg1=$(echo "${registros[$reg]}" | awk -F: '{print $3}' | sed 's/^0*//')
    seg2=$(echo "${registros[$reg+1]}" | awk -F: '{print $3}' | sed 's/^0*//')
    
    # Extrae los nanosegundos del registro actual y el siguiente, eliminando 
    # ceros a la izquierda.
    nano1=$(echo "${registros[$reg]}" | awk -F: '{print $NF}' | sed 's/^0*//')
    nano2=$(echo "${registros[$reg+1]}" | awk -F: '{print $NF}' | sed 's/^0*//')
    
    # Si los segundos son iguales, calcula la diferencia de nanosegundos y 
    # escribe en el archivo.
    if [ $seg1 -eq $seg2 ];then
	    echo $(( $nano2 - $nano1 )) >> $write_file
    else
        # Si los segundos son diferentes, calcula la diferencia considerando 
        # el paso de segundo.
        echo $(( $nano_per_seg - $nano1 + $nano2 )) >> $write_file
    fi
done