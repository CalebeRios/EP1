#include "../inc/trap.hpp"

using namespace std;

Trap::Trap(){
	setPositionX(0);
	setPositionY(0);
	setSprite('&');
	setDamage(1);
}

Trap::~Trap(){}

void Trap::setDamage(int damage){
	this->damage = damage;
}
int Trap::getDamage(){
	return damage;
}