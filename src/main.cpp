#include <ncurses.h>
#include <fstream>
#include <cstdlib>

using namespace std;

#include "../inc/bonus.hpp"
#include "../inc/mapa.hpp"
#include "../inc/player.hpp"
#include "../inc/trap.hpp"
#include "../inc/monster.hpp"
#include "../inc/arrival.hpp"

void menu(Player *player, Bonus *bonus[], Trap *trap[], Mapa *mapa_1, Arrival *arrival);
void inser_object(Player *player, Bonus *bonus[], Trap *trap[], Mapa *mapa_1, Arrival *arrival);
void destr_object(Player *player, Bonus *bonus[], Trap *trap[], Mapa *mapa_1, Arrival *arrival);
void inser_ranking(Player *player);
void game_loop(Player *player, Bonus *bonus[], Trap *trap[], Mapa *mapa_1, Arrival *arrival);

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
	Bonus *bonus[3];
	Trap *trap[4];

	menu(player, bonus, trap, mapa_1, arrival);

	refresh();

	endwin();
	return 0;
}

void menu(Player *player, Bonus *bonus[], Trap *trap[], Mapa *mapa_1, Arrival *arrival){
	clear();

	player->setWinner(false);
	player->setLife(3);

	printw("\t\t<< MENU >>\n");
	printw("1) Iniciar o jogo\n");
	printw("2) Ranking\n");
	printw("0) Sair\n");
	printw("Opção: ");
	char nome[30];
	int opc = getch();
	char ch;

	if(opc == '1'){
		clear();

		echo();

		printw("Nome: ");
		getstr(nome);
		player->setNome(nome);
		refresh();

		noecho();

		inser_object(player, bonus, trap, mapa_1, arrival);
		game_loop(player, bonus, trap, mapa_1, arrival);
	}
	else if(opc == '2'){
		clear();

		ifstream ranking;

		ranking.open("../doc/ranking.txt");

		while(ranking.get(ch) != '\0'){
			printw("%c", ch);
		}
		refresh();

		getch();

		menu(player, bonus, trap, mapa_1, arrival);

		ranking.close();
	}
	else if(opc == '0'){
		endwin();
		exit(0);
	}
	else
		menu(player, bonus, trap, mapa_1, arrival);
}

void inser_object(Player *player, Bonus *bonus[], Trap *trap[], Mapa *mapa_1, Arrival *arrival){
	clear();

	bonus[0] = new Bonus(20, 45);
	bonus[1] = new Bonus(04, 42);
	bonus[2] = new Bonus(24, 01);

	trap[0] = new Trap(22, 07);
	trap[1] = new Trap(06, 39);
	trap[2] = new Trap(20, 42);
	trap[3] = new Trap(24, 31);
	trap[4] = new Trap(10, 15);

	mvprintw(0, (mapa_1->getCol() - mapa_1->getCol()), "Score: %d", player->getScore());
	mvprintw(0, (mapa_1->getCol() - length(player->getNome()) ) / 2, "%s", player->getNome());
	mvprintw(0, (mapa_1->getCol() - 9), "Life: ");
	player->life_d(player->getLife());

	mapa_1->imprimir_mapa_1();

	mvaddch(player->getPositionX(), player->getPositionY(), player->getSprite());

	mvaddch(arrival->getPositionY(), arrival->getPositionX(), arrival->getSprite());

	mvaddch(bonus[0]->getPositionX(), bonus[0]->getPositionY(), bonus[0]->getSprite());
	mvaddch(bonus[1]->getPositionX(), bonus[1]->getPositionY(), bonus[1]->getSprite());
	mvaddch(bonus[2]->getPositionX(), bonus[2]->getPositionY(), bonus[2]->getSprite());

	mvaddch(trap[0]->getPositionX(), trap[0]->getPositionY(), trap[0]->getSprite());
	mvaddch(trap[1]->getPositionX(), trap[1]->getPositionY(), trap[1]->getSprite());
	mvaddch(trap[2]->getPositionX(), trap[2]->getPositionY(), trap[2]->getSprite());
	mvaddch(trap[3]->getPositionX(), trap[3]->getPositionY(), trap[3]->getSprite());
	mvaddch(trap[4]->getPositionX(), trap[4]->getPositionY(), trap[4]->getSprite());

	mvprintw((mapa_1->getRow() + 1), ((mapa_1->getCol() - 23) / 2), "Aperte <p> para pausar!");
}

void destr_object(Player *player, Bonus *bonus[], Trap *trap[], Mapa *mapa_1, Arrival *arrival){
	player->~Player();
	trap[0]->~Trap();
	trap[1]->~Trap();
	trap[2]->~Trap();
	trap[3]->~Trap();
	trap[4]->~Trap();
	bonus[0]->~Bonus();
	bonus[1]->~Bonus();
	bonus[2]->~Bonus();
	mapa_1->~Mapa();
	arrival->~Arrival();
}

void inser_ranking(Player *player){
		ofstream ranking;

		ranking.open("../doc/ranking.txt", ios_base::app);

		ranking.write(player->getNome(), sizeof(player->getNome()));
		ranking.put('\t');
		ranking.put('\t');
		ranking << player->getScore() << endl;
		refresh();

		ranking.close();
}

void game_loop(Player *player, Bonus *bonus[], Trap *trap[], Mapa *mapa_1, Arrival *arrival){
	int ch = getch();
	int row = player->getPositionX();
	int col = player->getPositionY();
	int opt = ch - 1;

	//player->setLife(0);

	for(;;){
		mvprintw((mapa_1->getRow() + 1), ((mapa_1->getCol() - 23) / 2), "Aperte <p> para pausar!");

		switch(ch){
			case KEY_LEFT:
				if(mvinch(row, col-1) == '-' || mvinch(row, col-1) == '|')
					refresh();
				else{
					if(mvinch(row, col-1) == '$')
						player->setScore(player->getScore() + 5);
					else if(mvinch(row, col-1) == '*')
						player->setLife(player->getLife() - trap[0]->getDamage());
					else if(mvinch(row, col-1) == '#')
						player->setWinner(true);		
					erase(row, col, ' ');
					col = col - 1;
					mvaddch(row, col, player->getSprite());
					refresh();
				}
				break;
		
			case KEY_RIGHT:
				if(mvinch(row, col + 1) == '-' || mvinch(row, col + 1) == '|' || col == mapa_1->getCol())
					refresh();
				else{
					if(mvinch(row, col + 1) == '$')
						player->setScore(player->getScore() + 5);
					else if(mvinch(row, col + 1) == '*')
						player->setLife(player->getLife() - trap[0]->getDamage());
					else if(mvinch(row, col + 1) == '#')
						player->setWinner(true);						
					erase(row, col, ' ');
					col = col + 1;
					mvaddch(row, col, player->getSprite());
					refresh();
				}
				break;

			case KEY_UP:
				if(mvinch(row - 1, col) == '-' || mvinch(row - 1, col) == '|')
					refresh();
				else{
					if(mvinch(row - 1, col) == '$')
						player->setScore(player->getScore() + 5);	
					else if(mvinch(row - 1, col) == '*')
						player->setLife(player->getLife() - trap[0]->getDamage());
					else if(mvinch(row - 1, col) == '#')
						player->setWinner(true);						
					erase(row, col, ' ');
					row = row - 1;
					mvaddch(row, col, player->getSprite());
					refresh();
				}
				break;

			case KEY_DOWN:
				if(mvinch(row + 1, col) == '-' || mvinch(row + 1, col) == '|')
					refresh();
				else{
					if(mvinch(row + 1, col) == '$')
						player->setScore(player->getScore() + 5);
					else if(mvinch(row + 1, col) == '*')
						player->setLife(player->getLife() - trap[0]->getDamage());
					else if(mvinch(row + 1, col) == '#')
						player->setWinner(true);	
					erase(row, col, ' ');
					row = row + 1;
					mvaddch(row, col, player->getSprite());
					refresh();
				}
				break;

			case 'p':
				mvprintw((mapa_1->getRow() + 1), ((mapa_1->getCol() - 38) / 2), "Game Paused! Press <enter> to continue");
				refresh();
				
				while (1){
					int key_press = getch();

			  		if (key_press == '\n'){
	  					mvprintw((mapa_1->getRow() + 1), 0, "                                              ");
						mvprintw((mapa_1->getRow() + 1), ((mapa_1->getCol() - 23) / 2), "Aperte <p> para pausar!");

			  			break;
					}
			   	}
				break;
		}

		mvprintw(0, 0, "Score: %d", player->getScore());
		mvprintw(0, (mapa_1->getCol() - 9), "Life: ");
		player->life_d(player->getLife());

		if(ch == 'q' || ch == 'Q'){
			menu(player, bonus, trap, mapa_1, arrival);
			break;
		}

		if(player->getWinner()){
			inser_ranking(player);

			mvprintw((mapa_1->getRow() + 1) / 2, (mapa_1->getCol() - 22) / 2, "Parabens! Você ganhou.");
			refresh();

			player->setLife(3);
			player->setScore(0);

			getch();

			menu(player, bonus, trap, mapa_1, arrival);
			return;
		}

		if(player->getLife() == 0){
			inser_ranking(player);
			mvprintw(mapa_1->getRow() / 2, (mapa_1->getCol() - 9) / 2, "You lose!");
			mvprintw((mapa_1->getRow() + 1) / 2, (mapa_1->getCol() - 36) / 2, "Aperte <enter> para jogar novamente,");
			mvprintw((mapa_1->getRow() + 3) / 2, (mapa_1->getCol() - 24) / 2, "ou aperte <q> para sair!");
			//while(1){
				opt = getch();
					if(opt == '\n'){
						player->setLife(3);
						player->setScore(0);
						inser_object(player, bonus, trap, mapa_1, arrival);
						game_loop(player, bonus, trap, mapa_1, arrival);
					}
					else if(opt == 'q' || opt == 'Q'){
						menu(player, bonus, trap, mapa_1, arrival);
						return;
					}
					else
						ch = '/';
			//}
		}
		if(opt == 'q')
			ch = opt;
		else
			ch = getch();

		mvprintw((mapa_1->getRow() + 1), ((mapa_1->getCol() - 38) / 2), "                                              ");
	}
}