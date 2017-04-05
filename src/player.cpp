#include "../inc/player.hpp"

using namespace std;

Player::Player(){
	setPositionX(18);
	setPositionY(39);
	setSprite('@');
	setAlive(true);
	setScore(0);
	setWinner(false);
}

Player::~Player(){}

void Player::setAlive(bool alive){
	this->alive = alive;
}
bool Player::getAlive(){
	return alive;
}

void Player::setScore(int score){
	this->score = score;
}
int Player::getScore(){
	return score;
}

void Player::setWinner(bool winner){
	this->winner = winner;
}
bool Player::getWinner(){
	return winner;
}
