#pragma once
#include "Vector.h"
#include "ETSIDI.h"
#include "Casilla.h"
#include "Pieza.h"

using ETSIDI::Sprite;

class Caballo : public Pieza
{
public:
    Caballo();
    Caballo(int _f, int _c, int _color);
    virtual ~Caballo() {};
    void dibuja();
    int getTipoPieza();

};
