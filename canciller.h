#pragma once
#include "Vector.h"
#include "ETSIDI.h"
#include "Casilla.h"
#include "Pieza.h"

using ETSIDI::Sprite;

class Canciller : public Pieza
{
public:
    Canciller();
    Canciller(int _f, int _c, int _color);
    virtual ~Canciller() {};
    void dibuja();
    int getTipoPieza();

};
