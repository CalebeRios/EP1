#include <ncurses.h>

using namespace std;

#include "../inc/bonus.hpp"
#include "../inc/gameobject.hpp"
#include "../inc/mapa.hpp"
#include "../inc/player.hpp"
#include "../inc/trap.hpp"

void erase (int y, int x, char ch) {
 	mvaddch(y, x, ch);
}

int main() {

	initscr();
	clear();
	noecho();
	cbreak();
	keypad(stdscr, TRUE);
	curs_set(0);

	Mapa *mapa_1 = new Mapa();
	Player *player = new Player();

	printw("Bem vindo ao jogo!\nAperte <enter> para continuar..\nOu q para sair.");

	int ch = getch();
	int row = player->getPositionX();
	int col = player->getPositionY();

	clear();

	if(ch == 'q'){
		endwin();
		return 0;
	}

	mapa_1->imprimir_mapa();
	mvaddch(row, col, player->getSprite());
	refresh();

	for(;;){
		ch = getch();

		if(ch == KEY_LEFT){
			erase(row, col, ' ');
			col = col - 1;
			mvaddch(row, col, player->getSprite());
			refresh();
		}
		else if(ch == KEY_RIGHT){
			erase(row, col, ' ');
			col = col + 1;
			mvaddch(row, col, player->getSprite());
			refresh();
		}
		else if(ch == KEY_UP){
			erase(row, col, ' ');
			row = row - 1;
			mvaddch(row, col, player->getSprite());
			refresh();
		}
		else if(ch == KEY_DOWN){
			erase(row, col, ' ');
			row = row + 1;
			mvaddch(row, col, player->getSprite());
			refresh();
		}
		else if(ch == 'q' || ch == 'Q'){
			break;
		}
	}

	endwin();
	return 0;
}