#include "../inc/bonus.hpp"

using namespace std;

Bonus::Bonus(){
	setPositionX(0);
	setPositionY(0);
	setSprite('$');
	setBonus(0);
}

Bonus::Bonus(int X, int Y){
	setPositionX(X);
	setPositionY(Y);
	setSprite('$');
	setBonus(0);
}

Bonus::~Bonus(){}

void Bonus::setBonus(int score){
	this->score = score;
}
int Bonus::getBonus(){
	return score;
}