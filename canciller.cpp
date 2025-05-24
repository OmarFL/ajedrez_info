#include "canciller.h"
#include "freeglut.h"

//Constructor de canciller predeterminado
Canciller::Canciller()
{
    canciller_w.setCenter(0, 0);
    canciller_w.setSize(1, 1);


    canciller_b.setCenter(0, 0);
    canciller_b.setSize(1, 1);

    estado = 0;
}

//Constructor de los cancillers blancos y negros
Canciller::Canciller(int _f, int _c, int _color) {
    canciller_w.setCenter(0, 0);
    canciller_w.setSize(1, 1);

    Vector pos1;
    posicion = pos1.conversor(_f, _c);

    canciller_b.setCenter(0, 0);
    canciller_b.setSize(1, 1);

    Vector pos2;
    posicion = pos2.conversor(_f, _c);
    color = _color;
    fc.setCasillas(_f, _c);
    estado = 0;
}

//Funcion para representar los cancillers
void Canciller::dibuja() {

    posicion = posicion.conversor(fc.getF(), fc.getC());

    if (color == 0) {
        glPushMatrix();
        glTranslatef(posicion.getX(), posicion.getY(), 0.5);
        glColor3f(1.0f, 0.0f, 0.0f);
        canciller_w.draw();
        glPopMatrix();
    }
    else {
        glPushMatrix();
        glTranslatef(posicion.getX(), posicion.getY(), 0.5);
        glColor3f(1.0f, 0.0f, 0.0f);
        canciller_b.draw();
        glPopMatrix();
    }
}

//Funcion para saber que tipo de pieza es 
int Canciller::getTipoPieza() {
    return 8;
}
