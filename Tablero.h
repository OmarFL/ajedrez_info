#pragma once
#include "Vector.h"
#include "Casilla.h"

class Tablero {
private:
	//Creacion del tablero
	Vector posicion;
	Casilla casillas[10][8];

	//Punto de vista del tablero
	float x_ojo;
	float y_ojo;
	float z_ojo;

public:
	Tablero();
	virtual ~Tablero() {};
	void inicializa();
	void dibuja();
};
