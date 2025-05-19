#pragma once
#include "Vector.h"
#include "ETSIDI.h"
#include "Casilla.h"
#include "Pieza.h"

using namespace std;

using ETSIDI::Sprite;

class Arzobispo : public Pieza {
public:
    Arzobispo();
    Arzobispo(int _f, int _c, int _color);
    virtual ~Arzobispo() {};
    void dibuja();
    int getTipoPieza();


};
