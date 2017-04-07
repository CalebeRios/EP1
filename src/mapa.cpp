#include <fstream>
#include <iostream>
#include <ncurses.h>
#include "../inc/mapa.hpp"

using namespace std;

int k = 0;

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

	ifstream fp;
	char ch;

	fp.open("../doc/mapa.txt");

	move(1, 0);

	for(int i = 0; i <= 20; ++i){
		for(int j = 0; j < 39; ++j){
			k++;
			fp.get(ch);
			printw("%c", ch);
		}
	}

	fp.close();	

	endwin();
}

// Verifica se o proximo caractere é um caractere improprio.
bool Mapa::caractere(int row, int col, char sprite){
	ifstream fp;
	char ch;

	fp.open("../doc/mapa.txt");

	for(int i = 0; i <= 20; ++i){
		for(int j = 0; j < 39; ++j){
			if(i == (row-1) && j == col)
				fp.get(ch);
				printw("%s", ch);
		}
	}

	fp.close();

	if(ch == sprite)
		return true;

	return false;
}