#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include <unistd.h>	//uso da função sleep
#include "snake.h"

//Const
const int nline = 20;
const int ncols = 40;

//Funçoes
void menu(WINDOW *);
void game(WINDOW *);
int *aloca(int);
void desenha(WINDOW *, Cobra *, int);

int main(){
	//Inicializaçoes
	int loc_x = 0, loc_y = 0, tam_snake = 4;	
	char flag_a = 0, flag_s = 0, flag_d = 0, flag_w = 0;
	
	//Iniciando j1
	Cobra j1;
	j1.n = 800;
	j1.x = aloca(j1.n);
	j1.y = aloca(j1.n);
	//Setando posição inicial
	for(int i = 0; i < tam_snake; i++){
		j1.x[i] = tam_snake - i;
		j1.y[i] = 1;
	}

	//Iniciando a janela-------------------------------
	initscr();
	noecho();			//não mostra caracter na janela
	cbreak();
	curs_set(0);		//esconde o cursor

	//timeout(500);

	scrollok(stdscr, TRUE);
	nodelay(stdscr, TRUE);

	//Criando a figura--------------------------------
	WINDOW * win = newwin(nline, ncols, loc_x, loc_y);
	refresh();
	box(win, 0, 0);
	wrefresh(win);

	//menu
	menu(win);

	//keypad(stdscr, TRUE);
	//loop
	while(1){
		//Movendo caracter
		//desenha(win, j1, tam_snake);
		mvwprintw(win, j1.y[0], j1.x[0], "X");	//LINHA   = y
		wrefresh(win);				//COLUNAS = x

		if(flag_w)
			j1.y[0]--;
		if(flag_s)
			j1.y[0]++;
		if(flag_d)
			j1.x[0]++;
		if(flag_a)
			j1.x[0]--;

		switch(getch()){
			case 'w':
				if((j1.y[0]-1) >= 1){
					j1.y[0]--;
					flag_w = 1;
					flag_a = 0;
					flag_s = 0;
					flag_d = 0;
				}
				break;
			case 's':
				if((j1.y[0]+1) < nline-1){
					j1.y[0]++;
					flag_w = 0;
					flag_a = 0;
					flag_s = 1;
					flag_d = 0;

				}
				break;
			case 'd':
				if((j1.x[0]+1) < ncols-1){
					j1.x[0]++;
					flag_w = 0;
					flag_a = 0;
					flag_s = 0;
					flag_d = 1;

				}
				break;
			case 'a':
				if((j1.x[0]-1) >= 1){
					j1.x[0]--;
					flag_w = 0;
					flag_a = 1;
					flag_s = 0;
					flag_d = 0;

				}
				break;
		}

		napms(300);	//Pausa de 0,5 segundos
	}
	
	//Fim
	free(j1.x);
	free(j1.y);
	delwin(win);
	endwin();

	return 0;
}

void desenha(WINDOW *win, Cobra *A, int tam){
	for(int i = 0; i < tam; i++){
		mvwprintw(win, A->x[i], A->y[i], "X");
		wrefresh(win);
	}
}

void swap(Cobra *A, int tam){
	for(int i = 0; i < tam; i++){
		
	}
}

void menu(WINDOW *win){
	//menu---------------------------------------------
	mvwprintw(win, 1, 1, "Star game press W,A,S or D");
	mvwprintw(win, 2, 1, "Quit game press Q");
	wrefresh(win);
	getch();
	mvwprintw(win, 1, 1, "                          ");
	mvwprintw(win, 2, 1, "                 ");
	wrefresh(win);
}

int *aloca(int n){
	int *x;
	x =  malloc(n * sizeof(int));
	return x;
}
