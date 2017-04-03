#ifndef GAMEOBJECT_HPP
#define GAMEOBJECT_HPP

#include <string>

class GameObject{
private:
	int positionX;
	int PositionY;
	char sprite;
public:
	virtual GameObject() = 0;
	~GameObject();

	void setPositionX(int);
	int getPositionX();

	void setPositionY(int);
	int getPositionY();

	void setSprite(char);
	char getSprite();
}

#endif