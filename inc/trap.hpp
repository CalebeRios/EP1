#ifndef TRAP_HPP
#define TRAP_HPP

#include "gameobject.hpp"

class Trap : public GameObject{
private:
	int damage;
public:
	Trap();
	~Trap();

	void setDamage(int);
	int getDamage();
};

#endif