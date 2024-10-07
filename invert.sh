file=$1

registros=($(cat $file))

rm $file

for reg in {99..0};do
    echo ${registros[reg]} >> $file
done
