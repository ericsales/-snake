all:
	gcc main.c snake.h -o main -lncurses

clear:
	rm main

run:
	./main
