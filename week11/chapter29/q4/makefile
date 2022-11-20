FLAGS=-Wall -pthread -g
CC=clang

all: standard_list hands_list


clean:
	rm standard_list

standard_list: standard_list.c
	$(CC) -o standard_list $(FLAGS) standard_list.c

hands_list: hands_list.c
	$(CC) -o hands_list $(FLAGS) hands_list.c
