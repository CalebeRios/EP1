#ifndef BONUS_HPP
#define BONUS_HPP

#include "gameobject.hpp"

using namespace std;

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