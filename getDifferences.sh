#!/bin/bash
read_file=""
write_file=""

if [[ $# -eq 0 || $# -lt 2 || $# -gt 2 ]];then
    echo "Error"
    echo "Usage: $0 readFile writeFile"
    exit 1
else
    read_file=$1
    write_file=$2

    echo "Reading from -> $read_file"
    echo "Writting to -> $write_file"
fi

registros=($(cat $read_file))

nano_per_seg=1000000000

# Read 101 rows to obtain and write 100 differences.
for reg in {0..98};do 
    seg1=$(echo "${registros[$reg]}" | awk -F: '{print $3}' | sed 's/^0*//')
    seg2=$(echo "${registros[$reg+1]}" | awk -F: '{print $3}' | sed 's/^0*//')
    
    nano1=$(echo "${registros[$reg]}" | awk -F: '{print $NF}' | sed 's/^0*//')
    nano2=$(echo "${registros[$reg+1]}" | awk -F: '{print $NF}' | sed 's/^0*//')
    
    if [ $seg1 -eq $seg2 ];then
	    echo $(( $nano2 - $nano1 )) >> $write_file
    else
        echo $(( $nano_per_seg - $nano1 + $nano2 )) >> $write_file
    fi

done
