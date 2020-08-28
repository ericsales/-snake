#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include <unistd.h>	//uso da função sleep
#include "snack.h"

//Funçoes
void menu(WINDOW *);
void game(WINDOW *);
int *aloca(int);

int main(){
	//Inicializaçoes
	int nline = 20, ncols = 40, loc_x = 0, loc_y = 0;	
	int l = 1, c = 1;
	char entrada;
	char flag_a = 1, flag_s = 1, flag_d = 1, flag_w = 1;
	//Iniciando j1
	Cobra j1;
	j1.n = 800;
	j1.x = aloca(j1.n);
	j1.y = aloca(j1.n);

	//Iniciando a janela-------------------------------
	initscr();
	noecho();		//não mostra caracter na janela
	cbreak();
	curs_set(0);		//esconde o cursor

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
		mvwprintw(win, l, c, "X");
		wrefresh(win);

		if(flag_w)
			l--;
		if(flag_s)
			l++;
		if(flag_d)
			c++;
		if(flag_a)
			c--;

		switch(getch()){
			case 'w':
				if((l-1) >= 1){
					mvwprintw(win, l, c, " ");
					l--;
					flag_w = 1;
					flag_a = 0;
					flag_s = 0;
					flag_d = 0;
				}
				break;
			case 's':
				if((l+1) < nline-1){
					mvwprintw(win, l, c, " ");
					l++;
					flag_w = 0;
					flag_a = 0;
					flag_s = 1;
					flag_d = 0;

				}
				break;
			case 'd':
				if((c+1) < ncols-1){
					mvwprintw(win, l, c, " ");
					c++;
					flag_w = 0;
					flag_a = 0;
					flag_s = 0;
					flag_d = 1;

				}
				break;
			case 'a':
				if((c-1) >= 1){
					mvwprintw(win, l, c, " ");
					c--;
					flag_w = 0;
					flag_a = 1;
					flag_s = 0;
					flag_d = 0;

				}
				break;
		}

		napms(500);	//Pausa de 0,5 segundos
	}
	
	//Fim
	free(j1.x);
	free(j1.y);
	delwin(win);
	endwin();

	return 0;
}


void menu(WINDOW * win){
	//menu---------------------------------------------
	mvwprintw(win, 1, 1, "Star game press W,A,S or D");
	mvwprintw(win, 2, 1, "Quit game press Q");
	wrefresh(win);
	getch();
}
/*
void game(WINDOW * win){
	//keypad(stdscr, TRUE);
	//loop
	while((entrada = getch()) != 'q'){
		//Movendo caracter
		mvwprintw(win, l, c, "X");
		wrefresh(win);

		switch(entrada){
			case 'w':
				if((l-1) >= 1){
					mvwprintw(win, l, c, " ");
					l--;
				}
				break;
			case 's':
				if((l+1) < nline-1){
					mvwprintw(win, l, c, " ");
					l++;
				}
				break;
			case 'd':
				if((c+1) < ncols-1){
					mvwprintw(win, l, c, " ");
					c++;
				}
				break;
			case 'a':
				if((c-1) >= 1){
					mvwprintw(win, l, c, " ");
					c--;
				}
				break;
			defaut:
				break;
		}
	}
}
*/
int *aloca(int n){
	int *x;
	x =  malloc(n * sizeof(int));
	return x;
}
