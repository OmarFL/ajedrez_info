#pragma once
#include "Vector.h"
#include "ETSIDI.h"
#include "Casilla.h"
#include "Pieza.h"

using ETSIDI::Sprite;

class Torre : public Pieza {

public:
    Torre();
    Torre(int _f, int _c, int _color);
    virtual ~Torre() {}
    void dibuja();
    int getTipoPieza();

};
