#include <fstream>
#include <iostream>
#include <ncurses.h>
#include "../inc/mapa.hpp"

using namespace std;

Mapa::Mapa(){
	setRow(25);
	setCol(47);
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

void Mapa::imprimir_mapa_1(){
	initscr();

	ifstream fp;
	char ch;

	fp.open("../doc/mapa_1.txt");

	move(1, 0);

	for(int i = 1; i <= 25; ++i){
		for(int j = 1; j <= 49; ++j){
			fp.get(ch);
			printw("%c", ch);
		}
	}

	fp.close();	

	endwin();
}

void Mapa::imprimir_mapa_2(){
	initscr();

	ifstream fp;
	char ch;

	fp.open("../doc/mapa_2.txt");

	move(1, 0);

	for(int i = 1; i <= 32; ++i){
		for(int j = 1; j <= 61; ++j){
			fp.get(ch);
			printw("%c", ch);
		}
	}

	fp.close();	

	endwin();
}
