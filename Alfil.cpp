#include "Alfil.h"
#include "freeglut.h"

//Constructor de alfil predeterminado
Alfil::Alfil()
{
    alfil_w.setCenter(0, 0);
    alfil_w.setSize(1, 1);
    

    alfil_b.setCenter(0, 0);
    alfil_b.setSize(1, 1);
    

    estado = 0;

}

//Constructor de los alfiles blancos y negros
Alfil::Alfil(int _f, int _c, int _color) {
    alfil_w.setCenter(0, 0);
    alfil_w.setSize(1, 1);
  
    Vector pos1;
    posicion = pos1.conversor(_f, _c);

    alfil_b.setCenter(0, 0);
    alfil_b.setSize(1, 1);
    
    Vector pos2;
    posicion = pos2.conversor(_f, _c);
    color = _color;
    estado = 0;
    fc.setCasillas(_f, _c);

}

//Funcion para representar los alfiles
void Alfil::dibuja() {

    posicion = posicion.conversor(fc.getF(), fc.getC());

    if (color == 0) {
        glPushMatrix();
        glTranslatef(posicion.getX(), posicion.getY(), 0.5);
        glColor3f(1.0f, 0.0f, 0.0f);
        alfil_w.draw();
        glPopMatrix();
    }
    else {
        glPushMatrix();
        glTranslatef(posicion.getX(), posicion.getY(), 0.5);
        glColor3f(1.0f, 0.0f, 0.0f);
        alfil_b.draw();
        glPopMatrix();
    }
}

//Funcion para saber que tipo de pieza es 
int Alfil::getTipoPieza() {
    return 3;

}
