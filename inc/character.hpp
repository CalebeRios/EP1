#ifndef CHARACTER_HPP
#define CHARACTER_HPP

#include "gameobject.hpp"

class Character : public GameObject{
private:
	int life;
public:
	Character();
	~Character();

	void setLife(bool);
	bool getLife();
};

#endif