for f in `ls *.elf`; do 
    echo $f 
    avr-size -C $f | grep Program
    avr-size -C $f | grep Data
done