#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "character.hpp"

using namespace std;

class Player : public Character{
private:
	int score;
	bool winner;
	char *nome;
public:
	Player();
	~Player();

	void setScore(int);
	int getScore();

	void setWinner(bool);
	bool getWinner();

	void setNome(char*);
	char * getNome();
};

#endif