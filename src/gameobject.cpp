#include "../inc/gameobject.hpp"

using namespace std;

GameObject::GameObject(){
	setPositionX(18);
	setPositionY(39);
	setSprite('@');
}

GameObject::~GameObject(){}

void GameObject::setPositionX(int positionX){
	this->positionX = positionX;
}
int GameObject::getPositionX(){
	return positionX;
}

void GameObject::setPositionY(int positionY){
	this->positionY = positionY;
}
int GameObject::getPositionY(){
	return positionY;
}

void GameObject::setSprite(char sprite){
	this->sprite = sprite;
}
char GameObject::getSprite(){
	return sprite;
}