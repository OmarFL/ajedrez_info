#pragma once
#include "Vector.h"
#include "ETSIDI.h"
#include "Casilla.h"
#include "Pieza.h"

using ETSIDI::Sprite;

class Dama : public Pieza
{
public:
    Dama();
    Dama(int _f, int _c, int _color);
    virtual ~Dama() {}
    void dibuja();
    int getTipoPieza();

};
