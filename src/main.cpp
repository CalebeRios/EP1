#include <ncurses.h>
#include <fstream>
#include <cstdlib>
#include <unistd.h>
#include <string.h>
#define tam_object 30

using namespace std;

#include "../inc/bonus.hpp"
#include "../inc/mapa.hpp"
#include "../inc/player.hpp"
#include "../inc/trap.hpp"
#include "../inc/monster.hpp"
#include "../inc/arrival.hpp"

void menu(Player *player, Bonus *bonus[], Trap *trap[], Mapa *mapa_1, Arrival *arrival);
void inser_object_1(Player *player, Bonus *bonus[], Trap *trap[], Mapa *mapa_1, Arrival *arrival);
void inser_object_2(Player *player, Bonus *bonus[], Trap *trap[], Mapa *mapa_1, Arrival *arrival);
void randObject(Bonus *bonus[], int i, int row, int col);
void randObject(Trap *trap[], int i, int row, int col);
void inser_ranking(Player *player);
void game_loop_1(Player *player, Bonus *bonus[], Trap *trap[], Mapa *mapa_1, Arrival *arrival);
void game_loop_2(Player *player, Bonus *bonus[], Trap *trap[], Mapa *mapa_1, Arrival *arrival);

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

int trand(int n){
	return 1 + (rand()%n);
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
	char nome[7];
	int opc = getch();
	char ch;

	if(opc == '1'){
		clear();

		echo();

		printw("Nome (Máximo 8 caracteres): ");
		getstr(nome);
		while(length(nome) > 8 || length(nome) == 0){
			clear();

			printw("Nome invalido!\nDigite novamente.");
			getch();
			refresh();

			clear();

			printw("Nome (Máximo 8 caracteres): ");
			getstr(nome);
			
			refresh();
		}
		player->setNome(nome);
		refresh();

		noecho();

		inser_object_1(player, bonus, trap, mapa_1, arrival);
		game_loop_1(player, bonus, trap, mapa_1, arrival);
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

void inser_object_1(Player *player, Bonus *bonus[], Trap *trap[], Mapa *mapa_1, Arrival *arrival){
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
	mvprintw((mapa_1->getRow() + 2), ((mapa_1->getCol() - 7) / 2), "Legenda");
	mvprintw((mapa_1->getRow() + 3), ((mapa_1->getCol() - 23) / 2), "@ - Player");
	mvprintw((mapa_1->getRow() + 4), ((mapa_1->getCol() - 23) / 2), "$ - Bonus");
	mvprintw((mapa_1->getRow() + 5), ((mapa_1->getCol() - 23) / 2), "* - Trap");
	mvprintw((mapa_1->getRow() + 6), ((mapa_1->getCol() - 23) / 2), "'q' - Sair");
}

void randObject(Bonus *bonus[], int i, int row, int col){
	srand((unsigned) time(NULL));

	bonus[i]->setPositionY(trand(32));
	bonus[i]->setPositionX(trand(58));

	while(mvinch(bonus[i]->getPositionY(), bonus[i]->getPositionX()) == '-' || mvinch(bonus[i]->getPositionY(), bonus[i]->getPositionX()) == '$' || mvinch(bonus[i]->getPositionY(), bonus[i]->getPositionX()) == '|' || mvinch(bonus[i]->getPositionY(), bonus[i]->getPositionX()) == '#' || mvinch(bonus[i]->getPositionY(), bonus[i]->getPositionX()) == '*' || mvinch(bonus[i]->getPositionY(), bonus[i]->getPositionX()) == '+' || bonus[i]->getPositionY() == row + 1 || bonus[i]->getPositionY() == row - 1 || bonus[i]->getPositionX() == col + 1 || bonus[i]->getPositionX() == col - 1){
		bonus[i]->setPositionY(trand(32));
		bonus[i]->setPositionX(trand(58));
	}

	mvaddch(bonus[i]->getPositionY(), bonus[i]->getPositionX(), bonus[i]->getSprite());
}

void randObject(Trap *trap[], int i, int row, int col){
	srand((unsigned) time(NULL));

	trap[i]->setPositionY(trand(32));
	trap[i]->setPositionX(trand(58));

	while(mvinch(trap[i]->getPositionY(), trap[i]->getPositionX()) == '-' || mvinch(trap[i]->getPositionY(), trap[i]->getPositionX()) == '$' || mvinch(trap[i]->getPositionY(), trap[i]->getPositionX()) == '|' || mvinch(trap[i]->getPositionY(), trap[i]->getPositionX()) == '#' || mvinch(trap[i]->getPositionY(), trap[i]->getPositionX()) == '*' || mvinch(trap[i]->getPositionY(), trap[i]->getPositionX()) == '+' || trap[i]->getPositionY() == row + 1 || trap[i]->getPositionY() == row - 1 || trap[i]->getPositionX() == col + 1 || trap[i]->getPositionX() == col - 1){
		trap[i]->setPositionY(trand(32));
		trap[i]->setPositionX(trand(58));
	}

	mvaddch(trap[i]->getPositionY(), trap[i]->getPositionX(), trap[i]->getSprite());
}

void inser_ranking(Player *player){
		ofstream ranking;
		int tam;

		ranking.open("../doc/ranking.txt", ios_base::app);

		ranking.write(player->getNome(), sizeof(player->getNome()));
		tam = length(player->getNome());

		for(int i = 0; i < 13 - tam; ++i)
			ranking.put(' ');
		
		ranking << player->getScore() << endl;
		refresh();

		ranking.close();
}

void game_loop_1(Player *player, Bonus *bonus[], Trap *trap[], Mapa *mapa_1, Arrival *arrival){
	int ch = getch();
	int row = player->getPositionX();
	int col = player->getPositionY();
	int opt = ch - 1;

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
			int opc;

			mvprintw((mapa_1->getRow() + 1) / 2, 0, "            Parabens! Você ganhou.            \n       Para voltar ao menu pressione <q>\n      ou para continuar pressione <enter>.                 ");
			refresh();

			player->setWinner(false);

			opc = getch();

			while(1){
				if(opc == 'q' || opc == 'Q'){
					menu(player, bonus, trap, mapa_1, arrival);
				}
				else if(opc == '\n'){
					clear();

					mvprintw(10, 15, "Fase 2");
					refresh();

					sleep(2);

					Trap *trap[tam_object];
					Bonus *bonus[tam_object];

					inser_object_2(player, bonus, trap, mapa_1, arrival);
					game_loop_2(player, bonus, trap, mapa_1, arrival);					
				}
				opc = getch();
			}
				return;

		}

		if(player->getLife() == 0){
			mvprintw(mapa_1->getRow() / 2, (mapa_1->getCol() - 9) / 2, "You lose!");
			mvprintw((mapa_1->getRow() + 1) / 2, (mapa_1->getCol() - 36) / 2, "Aperte <enter> para jogar novamente,");
			mvprintw((mapa_1->getRow() + 3) / 2, (mapa_1->getCol() - 24) / 2, "ou aperte <q> para sair!");
				opt = getch();
					if(opt == '\n'){
						player->setLife(3);
						player->setScore(0);
						inser_object_1(player, bonus, trap, mapa_1, arrival);
						game_loop_1(player, bonus, trap, mapa_1, arrival);
					}
					else if(opt == 'q' || opt == 'Q'){
						menu(player, bonus, trap, mapa_1, arrival);
						return;
					}
					else
						ch = '/';
		}
		if(opt == 'q')
			ch = opt;
		else
			ch = getch();

		mvprintw((mapa_1->getRow() + 1), ((mapa_1->getCol() - 38) / 2), "                                              ");
	}
}

void inser_object_2(Player *player, Bonus *bonus[], Trap *trap[], Mapa *mapa_1, Arrival *arrival){
	clear();

	for(int i = 0; i < tam_object; ++i){
		bonus[i] = new Bonus();
		trap[i] = new Trap();
	}


	mvprintw(0, (mapa_1->getCol() - mapa_1->getCol()), "Score: %d", player->getScore());
	mvprintw(0, ((mapa_1->getCol() + 13) - length(player->getNome()) ) / 2, "%s", player->getNome());
	mvprintw(0, 50, "Life: ");
	player->life_d_2(player->getLife());

	mapa_1->imprimir_mapa_2();

	mvaddch(player->getPositionX(), player->getPositionY(), player->getSprite());

	mvaddch(arrival->getPositionY() - 6, arrival->getPositionX() + 12, arrival->getSprite());

	mvprintw((mapa_1->getRow() + 8), ((mapa_1->getCol() - 10) / 2), "Aperte <p> para pausar!");
	mvprintw((mapa_1->getRow() + 9), ((mapa_1->getCol() - 7) / 2), "Legenda");
	mvprintw((mapa_1->getRow() + 10), ((mapa_1->getCol() - 10) / 2), "@ - Player");
	mvprintw((mapa_1->getRow() + 11), ((mapa_1->getCol() - 10) / 2), "$ - Bonus");
	mvprintw((mapa_1->getRow() + 12), ((mapa_1->getCol() - 10) / 2), "* - Trap");
	mvprintw((mapa_1->getRow() + 13), ((mapa_1->getCol() - 10) / 2), "'q' - Sair");
}

void game_loop_2(Player *player, Bonus *bonus[], Trap *trap[], Mapa *mapa_1, Arrival *arrival){
	int ch = getch();
	int row = player->getPositionX();
	int col = player->getPositionY();
	int opt = ch - 1;

	int j = 0;

	int life = player->getLife();
	int score = player->getScore();

	for(;;){
		mvprintw((mapa_1->getRow() + 8), ((mapa_1->getCol() - 10) / 2), "Aperte <p> para pausar!");

		if((j%5) == 0)
			for(int i = 0; i < tam_object; ++i){
				randObject(bonus, i, row, col);
				randObject(trap, i, row, col);
			}		

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
				if(mvinch(row, col + 1) == '-' || mvinch(row, col + 1) == '|')
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
				mvprintw((mapa_1->getRow() + 8), ((mapa_1->getCol() - 30) / 2), "Game Paused! Press <enter> to continue");
				refresh();
				
				while (1){
					int key_press = getch();

			  		if (key_press == '\n'){
	  					mvprintw((mapa_1->getRow() + 8), 0, "                                              ");
						mvprintw((mapa_1->getRow() + 8), ((mapa_1->getCol() - 10) / 2), "Aperte <p> para pausar!");

			  			break;
					}
			   	}
				break;

			default:

				break;
		}

		if((j%5) == 4){
			for(int i = 0; i < tam_object; ++i){
				if(mvinch(bonus[i]->getPositionY(), bonus[i]->getPositionX()) == '@'){
					erase(bonus[i]->getPositionY(), bonus[i]->getPositionX(), '@');
					erase(trap[i]->getPositionY(), trap[i]->getPositionX(), ' ');	
				}
				else if(mvinch(trap[i]->getPositionY(), trap[i]->getPositionX()) == '@'){
					erase(trap[i]->getPositionY(), trap[i]->getPositionX(), '@');
					erase(bonus[i]->getPositionY(), bonus[i]->getPositionX(), ' ');	
				}											
				else{
					erase(bonus[i]->getPositionY(), bonus[i]->getPositionX(), ' ');
					erase(trap[i]->getPositionY(), trap[i]->getPositionX(), ' ');	
				}
			}
		}

		mvprintw(0, 0, "Score: %d", player->getScore());
		mvprintw(0, 50, "Life: ");
		player->life_d_2(player->getLife());
		refresh();

		if(ch == 'q' || ch == 'Q'){
			menu(player, bonus, trap, mapa_1, arrival);
			break;
		}

		if(player->getWinner()){
			inser_ranking(player);

			mvprintw(16, 0, "                   Parabens! Você ganhou.                   ");
			refresh();

			player->setLife(3);
			player->setScore(0);

			getch();

			menu(player, bonus, trap, mapa_1, arrival);
			return;
		}

		if(player->getLife() == 0){
			mvprintw(16, 0, "                          You lose!                         ");
			mvprintw(17, 0, "            Aperte <enter> para jogar novamente,            ");
			mvprintw(18, 0, "                  ou aperte <q> para sair!                  ");

			opt = getch();

			if(opt == '\n'){
				player->setLife(life);
				player->setScore(score);
				inser_object_2(player, bonus, trap, mapa_1, arrival);
				game_loop_2(player, bonus, trap, mapa_1, arrival);
			}
			else if(opt == 'q' || opt == 'Q'){
				menu(player, bonus, trap, mapa_1, arrival);
				return;
			}
			else
				ch = '/';
		}
		if(opt == 'q')
			ch = opt;
		else
			ch = getch();

		mvprintw((mapa_1->getRow() + 8), ((mapa_1->getCol() - 38) / 2), "                                              ");	
		
		refresh();
		++j;
	}
}