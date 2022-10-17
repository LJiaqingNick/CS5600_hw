#!bin/bash
gcc -Wall -O0 tlb.c -o tlb
num_page=1
max_pages=4000
num_trials=100000
while [ $num_page -lt $max_pages ]
do
  ./tlb $num_page $num_trials | tee -a data.txt
  num_page=$((num_page*2))
  echo num_page
done