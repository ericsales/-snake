all:
	gcc main.c snack.h -o main -lncurses

clear:
	rm main

run:
	./main
