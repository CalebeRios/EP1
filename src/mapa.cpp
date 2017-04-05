#include <fstream>
#include <iostream>
#include <ncurses.h>
#include "../inc/mapa.hpp"

using namespace std;

Mapa::Mapa(){
	setRow(19);
	setCol(39);
}

Mapa::~Mapa(){}

void Mapa::setRow(int row){
	this->row = row;
}
int Mapa::getRow(){
	return row;
}

void Mapa::setCol(int col){
	this->col = col;
}
int Mapa::getCol(){
	return col;
}

void Mapa::imprimir_mapa(){
	initscr();
	clear();

	ifstream fp;
	char ch;

	fp.open("../doc/mapa.txt");

	for(int i = 0; i <= 20; ++i){
		for(int j = 0; j < 39; ++j){
			fp.get(ch);
			printw("%c", ch);
		}
	}

	fp.close();	

	endwin();
}