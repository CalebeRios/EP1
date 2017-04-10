#include "../inc/player.hpp"

using namespace std;

Player::Player(){
	setPositionX(2);
	setPositionY(1);
	setSprite('@');
	setLife(3);
	setScore(0);
	setWinner(false);
	//setNome();
}

Player::~Player(){}

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

void Player::setNome(char *nome){
	this->nome = nome;
}

char * Player::getNome(){
	return nome;
}