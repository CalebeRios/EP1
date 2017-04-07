#include "../inc/monster.hpp"

using namespace std;

Monster::Monster(){
	setPositionX(1);
	setPositionY(1);
	setSprite('%');
	setLife(1);
}

Monster::~Monster(){}
