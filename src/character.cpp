#include "../inc/character.hpp"

using namespace std;

Character::Character(){
	setPositionX(19);
	setPositionY(39);
	setSprite('!');
	setLife(0);	
}

Character::~Character(){}

void Character::setLife(bool life){
	this->life = life;
}
bool Character::getLife(){
	return life;
}
