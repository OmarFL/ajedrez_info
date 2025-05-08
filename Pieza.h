#pragma once
#include "Vector.h"
#include "Casilla.h"
#include "ETSIDI.h"
#include<iostream>
#include<cstring>


using ETSIDI::Sprite;

class Pieza
{
protected:
	
	Vector posicion;
	int estado,color;
	Casilla fc;

	//Declaracion de los diferentes figuras
	Sprite torre_w{ "imagenes/torre_w.png", 5 };
	Sprite torre_b{ "imagenes/torre_b.png", 5 };
	Sprite caballo_w{ "imagenes/caballo_w.png", 5 };
	Sprite caballo_b{ "imagenes/caballo_b.png", 5 };
	Sprite alfil_w{ "imagenes/alfil_w.png", 5 };
	Sprite alfil_b{ "imagenes/alfil_b.png", 5 };
	Sprite rey_w{ "imagenes/rey_w.png", 5 };
	Sprite rey_b{ "imagenes/rey_b.png", 5 };
	Sprite dama_w{ "imagenes/dama_w.png", 5 };
	Sprite dama_b{ "imagenes/dama_b.png", 5 };
	Sprite peon_w{ "imagenes/peon_w.png", 5 };
	Sprite peon_b{ "imagenes/peon_b.png", 5 };
	Sprite arzobispo_w{ "imagenes/arzobispo_w.png", 5 };
	Sprite arzobispo_b{ "imagenes/arzobispo_b.png", 5 };
	Sprite canciller_w{ "imagenes/canciller_w.png", 5 };
	Sprite canciller_b{ "imagenes/canciller_b.png", 5 };
	
public:
	virtual void dibuja();
	virtual void setPos(int _f, int _c);
	virtual int getTipoPieza();
	int getColor();
	int getfila();
	int getcolumna();
	Casilla getCasilla();
	
};
