#pragma once

class Selector
{
private:
	int fila, columna;
public:
	Selector();
	void inicializa();
	void mover(unsigned char key);
	int getFila();
	int getColumna();
	void reinicio();
	void setPos(int _fila, int _columna);
	
};
