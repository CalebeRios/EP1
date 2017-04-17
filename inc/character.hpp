#ifndef CHARACTER_HPP
#define CHARACTER_HPP

#include "gameobject.hpp"

class Character : public GameObject{
private:
	int life;
public:
	Character();
	~Character();

	void setLife(int);
	int getLife();

	void life_d(int);
	void life_d_2(int);

};

#endif