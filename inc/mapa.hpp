#ifndef MAPA_HPP
#define MAPA_HPP

using namespace std;

class Mapa{
private:
	int row;
	int col;
public:
	Mapa();
	~Mapa();

	void setRow(int);
	int getRow();

	void setCol(int);
	int getCol();

	void imprimir_mapa_1();
	void imprimir_mapa_2();
};

#endif