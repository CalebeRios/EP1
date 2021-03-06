#include <ncurses.h>

#include "../inc/character.hpp"

using namespace std;

Character::Character(){
	setPositionX(19);
	setPositionY(39);
	setSprite('!');
	setLife(0);	
}

Character::~Character(){}

void Character::setLife(int life){
	this->life = life;
}
int Character::getLife(){
	return life;
}

void Character::life_d(int life){
	if(life == 0)
		mvprintw(0, 44, "\n");
	else if(life == 1)
		mvprintw(0, 44, "*\n");
	else if(life == 2)
		mvprintw(0, 44, "**\n");
	else if(life == 3)
		mvprintw(0, 44, "***\n");
}

void Character::life_d_2(int life){
	if(life == 1)
		mvprintw(0, 56, "*\n");
	else if(life == 2)
		mvprintw(0, 56, "**\n");
	else if(life == 3)
		mvprintw(0, 56, "***\n");
}

