#pragma once
#include "Tablero.h"
#include "ETSIDI.h"
using ETSIDI::Sprite;


class CoordinadorAjedrez
{
public:
	CoordinadorAjedrez();
	virtual ~CoordinadorAjedrez();
	void dibuja();
	

protected:
	Tablero tablero;
	enum Estado { INICIO };
	Estado estado;
	Sprite sprite1{ "imagenes/inicio.png", 5 };
};