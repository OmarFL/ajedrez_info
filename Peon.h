#pragma once
#include "Vector.h"
#include "ETSIDI.h"
#include "Casilla.h"
#include "Pieza.h"

using ETSIDI::Sprite;


class Peon : public Pieza
{
public:
	Peon();
	Peon(int _f, int _c, int _color);
	virtual ~Peon() {}
	void dibuja() override;
	int getTipoPieza() override;
	void setposicion(Vector& posicion);
};
