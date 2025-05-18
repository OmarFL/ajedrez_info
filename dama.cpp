#include "Dama.h"
#include "freeglut.h"

//Constructor de dama predeterminado
Dama::Dama()
{
    dama_w.setCenter(0, 0);
    dama_w.setSize(1, 1);
   

    dama_b.setCenter(0, 0);
    dama_b.setSize(1, 1);
    
}

//Constructor de las damas blancas y negras
Dama::Dama(int _f, int _c, int _color) {
    dama_w.setCenter(0, 0);
    dama_w.setSize(1, 1);
    
    Vector pos1;
    posicion = pos1.conversor(_f, _c);

    dama_b.setCenter(0, 0);
    dama_b.setSize(1, 1);
    
    Vector pos2;
    posicion = pos2.conversor(_f, _c);
    color = _color;
    fc.setCasillas(_f, _c);
    estado = 0;
}

//Funcion para representar las damas
void Dama::dibuja() {

    posicion = posicion.conversor(fc.getF(), fc.getC());

    if (color == 0) {
        glPushMatrix();
        glTranslatef(posicion.getX(), posicion.getY(), 0.5);
        glColor3f(1.0f, 0.0f, 0.0f);
        dama_w.draw();
        glPopMatrix();
    }
    else {
        glPushMatrix();
        glTranslatef(posicion.getX(), posicion.getY(), 0.5);
        glColor3f(1.0f, 0.0f, 0.0f);
        dama_b.draw();
        glPopMatrix();
    }
}

//Funcion para saber que tipo de pieza es 
int Dama::getTipoPieza() {
    return 4;
}
