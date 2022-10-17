#!bin/bash
rm data.txt
gcc -Wall -O0 tlb.c -o tlb
num_page=1
max_pages=1500
num_trials=1000000
while [ $num_page -lt $max_pages ]
do
  ./tlb $num_page $num_trials | tee -a data.txt
  num_page=$((num_page*2))
done