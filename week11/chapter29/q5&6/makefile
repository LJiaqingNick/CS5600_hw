FLAGS=-Wall -pthread -g
CC=clang

all: stand_stack advance_stack

clean:
	rm stand_stack advance_stack

stand_stack: stand_stack.c
	$(CC) -o stand_stack $(FLAGS) stand_stack.c

hands_list: advance_stack.c
	$(CC) -o advance_stack $(FLAGS) advance_stack.c
