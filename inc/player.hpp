#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "gameobject.hpp"

class Player : public GameObject{
private:
	bool alive;
	int score;
	bool winner;
public:
	Player();
	~Player();

	void setAlive(bool);
	bool getAlive();

	void setScore(int);
	int getScore();

	void setWinner(bool);
	bool getWinner();
};

#endif