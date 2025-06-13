#pragma once
#include "Vector.h"
#include "Casilla.h"

class Tablero {
private:
	//Creacion del tablero
	//Vector posicion;
	Casilla casillas[10][8];

public:
	//Tablero();
	//void inicializa();
	void dibuja();
};
