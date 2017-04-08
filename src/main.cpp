#include <ncurses.h>

using namespace std;

#include "../inc/bonus.hpp"
#include "../inc/mapa.hpp"
#include "../inc/player.hpp"
#include "../inc/trap.hpp"
#include "../inc/monster.hpp"
#include "../inc/arrival.hpp"

void erase (int y, int x, char ch) {
 	mvaddch(y, x, ch);
}

int length(char *nome){
	int len = 0;

	while(nome[len] != '\0'){
		++len;
	}
	return len;
}

void inser_object(Player *player, Bonus *bonus[], Trap *trap[], Mapa *mapa_1, Arrival *arrival){
	clear();

	bonus[0] = new Bonus(4, 5);
	bonus[1] = new Bonus(17, 9);
	bonus[2] = new Bonus(6, 29);

	trap[0] = new Trap(6, 5);
	trap[1] = new Trap(12, 9);
	trap[2] = new Trap(8, 32);
	trap[3] = new Trap(17, 38);
	trap[4] = new Trap(10, 18);

	mvprintw(0, (mapa_1->getCol() - mapa_1->getCol()), "Score: %d", player->getScore());
	mvprintw(0, (mapa_1->getCol() - length(player->getNome()) ) / 2, "%s", player->getNome());
	mvprintw(0, (mapa_1->getCol() - 8), "Life: ");
	player->life_d(player->getLife());

	mapa_1->imprimir_mapa();

	mvaddch(player->getPositionX(), player->getPositionY(), player->getSprite());

	mvaddch(arrival->getPositionX(), arrival->getPositionY(), arrival->getSprite());

	mvaddch(bonus[0]->getPositionX(), bonus[0]->getPositionY(), bonus[0]->getSprite());
	mvaddch(bonus[1]->getPositionX(), bonus[1]->getPositionY(), bonus[1]->getSprite());
	mvaddch(bonus[2]->getPositionX(), bonus[2]->getPositionY(), bonus[2]->getSprite());

	mvaddch(trap[0]->getPositionX(), trap[0]->getPositionY(), trap[0]->getSprite());
	mvaddch(trap[1]->getPositionX(), trap[1]->getPositionY(), trap[1]->getSprite());
	mvaddch(trap[2]->getPositionX(), trap[2]->getPositionY(), trap[2]->getSprite());
	mvaddch(trap[3]->getPositionX(), trap[3]->getPositionY(), trap[3]->getSprite());
	mvaddch(trap[4]->getPositionX(), trap[4]->getPositionY(), trap[4]->getSprite());

	mvprintw((mapa_1->getRow() + 2), (mapa_1->getCol() - 31), "Aperte <p> para pausar!");
}

void game_loop(Player *player, Bonus *bonus[], Trap *trap[], Mapa *mapa_1, Arrival *arrival){
	int ch = getch();
	int row = player->getPositionX();
	int col = player->getPositionY();
	int opt = ch - 1;

	for(;;){
		mvprintw((mapa_1->getRow() + 2), (mapa_1->getCol() - 31), "Aperte <p> para pausar!");

		switch(ch){
			case KEY_LEFT:
				if(mvinch(row, col-1) == '+')
					refresh();
				else{
					if(mvinch(row, col-1) == '$')
						player->setScore(player->getScore()+5);
					else if(mvinch(row, col-1) == '&')
						player->setLife(player->getLife()-1);
				//	else if(mvinch(row, col-1) == '#')
						
					erase(row, col, ' ');
					col = col - 1;
					mvaddch(row, col, player->getSprite());
					refresh();
				}
				break;
		
			case KEY_RIGHT:
				if(mvinch(row, col + 1) == '+' || col == mapa_1->getCol())
					refresh();
				else{
					if(mvinch(row, col + 1) == '$')
						player->setScore(player->getScore()+5);
					else if(mvinch(row, col + 1) == '&')
						player->setLife(player->getLife()-1);
					erase(row, col, ' ');
					col = col + 1;
					mvaddch(row, col, player->getSprite());
					refresh();
				}
				break;

			case KEY_UP:
				if(mvinch(row-1, col) == '+')
					refresh();
				else{
					if(mvinch(row-1, col) == '$')
						player->setScore(player->getScore()+5);	
					else if(mvinch(row-1, col) == '&')
						player->setLife(player->getLife()-1);
					erase(row, col, ' ');
					row = row - 1;
					mvaddch(row, col, player->getSprite());
					refresh();
				}
				break;

			case KEY_DOWN:
				if(mvinch(row+1, col) == '+')
					refresh();
				else{
					if(mvinch(row+1, col) == '$')
						player->setScore(player->getScore()+5);
					else if(mvinch(row+1, col) == '&')
						player->setLife(player->getLife()-1);
					erase(row, col, ' ');
					row = row + 1;
					mvaddch(row, col, player->getSprite());
					refresh();
				}
				break;

			case 'p':
				mvprintw((mapa_1->getRow() + 2), (mapa_1->getCol() - 38), "Game Paused! Press <enter> to continue");
				refresh();
				
				while (1){
					int key_press = getch();

			  		if (key_press == '\n'){
	  					mvprintw((mapa_1->getRow() + 2), 0, "                                              ");
						mvprintw((mapa_1->getRow() + 2), (mapa_1->getCol() - 31), "Aperte <p> para pausar!");

			  			break;
					}
			   	}
				break;
		}

		if(ch == 'q' || ch == 'Q')
			break;

		mvprintw(0, 0, "Score: %d", player->getScore());
		mvprintw(0, 31, "Life: ");
		player->life_d(player->getLife());

		if(player->getLife() == 0){
			clear();
			printw("You lose!\nAperte <enter> para jogar novamente,\n ou aperte 'q' para sair!");
			while(1){
				opt = getch();
					if(opt == '\n'){
						player->setLife(3);
						inser_object(player, bonus, trap, mapa_1, arrival);
						game_loop(player, bonus, trap, mapa_1, arrival);
					}
					else if(opt == 'q' || opt == 'Q'){
						break;
					}
			}
		}
		if(opt == 'q')
			ch = opt;
		else
			ch = getch();

		mvprintw((mapa_1->getRow() + 2), 0, "                                              ");
	}
}

void menu(Player *player, Bonus *bonus[], Trap *trap[], Mapa *mapa_1, Arrival *arrival){
	printw("\t\t<< MENU >>\n");
	printw("1) Iniciar o jogo\n");
	printw("2) Ranking\n");
	printw("0) Sair\n");
	printw("Opção: ");
	char nome[30];
	int opc = getch();

	switch(opc){
		case '1':
			clear();

			echo();

			printw("Nome: ");
			getstr(nome);
			player->setNome(nome);
			refresh();

			noecho();

			inser_object(player, bonus, trap, mapa_1, arrival);
			game_loop(player, bonus, trap, mapa_1, arrival);
			break;
		case 2:
			clear();
			break;
		case 0:
			break;
	}
}

int main() {

	initscr();
	clear();
	noecho();
	raw();
	keypad(stdscr, TRUE);
	curs_set(0);

	Mapa *mapa_1 = new Mapa();
	Player *player = new Player();
	Arrival *arrival = new Arrival();
	Bonus *bonus[2];
	Trap *trap[4];

	menu(player, bonus, trap, mapa_1, arrival);

	refresh();

	endwin();
	return 0;
}