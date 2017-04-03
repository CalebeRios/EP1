#ifndef BONUS_HPP
#define BONUS_HPP

#include "gameobject.hpp"

class Bonus : public GameObject{
private:
	int score;
public:
	Bonus();
	~Bonus();

	void setBonus(int);
	int getBonus();
};

#endif