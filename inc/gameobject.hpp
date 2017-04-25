#ifndef GAMEOBJECT_HPP
#define GAMEOBJECT_HPP

using namespace std;

class GameObject{
private:
	int positionX;
	int positionY;
	char sprite;
public:
	GameObject();
	virtual ~GameObject() = 0;

	void setPositionX(int);
	int getPositionX();

	void setPositionY(int);
	int getPositionY();

	void setSprite(char);
	char getSprite();
};

#endif