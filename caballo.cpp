#include "Caballo.h"
#include "freeglut.h"

//Constructor de caballo predeterminado
Caballo::Caballo()
{
    caballo_w.setCenter(0, 0);
    caballo_w.setSize(1, 1);
    

    caballo_b.setCenter(0, 0);
    caballo_b.setSize(1, 1);
    
    estado = 0;
}

//Constructor de los caballos blancos y negros
Caballo::Caballo(int _f, int _c, int _color) {
    caballo_w.setCenter(0, 0);
    caballo_w.setSize(1, 1);
    
    Vector pos1;
    posicion = pos1.conversor(_f, _c);

    caballo_b.setCenter(0, 0);
    caballo_b.setSize(1, 1);
    
    Vector pos2;
    posicion = pos2.conversor(_f, _c);
    color = _color;
    fc.setCasillas(_f, _c);
    estado = 0;
}

//Funcion para representar los caballos
void Caballo::dibuja() {

    posicion = posicion.conversor(fc.getF(), fc.getC());

    if (color == 0) {
        glPushMatrix();
        glTranslatef(posicion.getX(), posicion.getY(), 0.5);
        glColor3f(1.0f, 0.0f, 0.0f);
        caballo_w.draw();
        glPopMatrix();
    }
    else {
        glPushMatrix();
        glTranslatef(posicion.getX(), posicion.getY(), 0.5);
        glColor3f(1.0f, 0.0f, 0.0f);
        caballo_b.draw();
        glPopMatrix();
    }
}

//Funcion para saber que tipo de pieza es 
int Caballo::getTipoPieza() {
    return 2;
}
