#ifndef TRAP_HPP
#define TRAP_HPP

#include "gameobject.hpp"

using namespace std;

class Trap : public GameObject{
private:
	int damage;
public:
	Trap();
	Trap(int, int);
	~Trap();

	void setDamage(int);
	int getDamage();
};

#endif