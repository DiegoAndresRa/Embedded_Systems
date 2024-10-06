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

# Read 101 rows to obtain and write 100 differences.
for reg in {0..99};do 
    item1=$(echo "${registros[$reg]}" | awk -F: '{print $NF}' | sed 's/^0*//')
    item2=$(echo "${registros[$reg+1]}" | awk -F: '{print $NF}' | sed 's/^0*//')
    
    if [ $item2 -lt $item1 ];then
	    echo $(( 1000000000 - $item1 + $item2 )) >> $write_file
    else
	    echo $(( $item2 - $item1 )) >> $write_file
    fi
done
