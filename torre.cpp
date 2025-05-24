#include "Torre.h"
#include "freeglut.h"

//Constructor de torre predeterminado
Torre::Torre()
{
    torre_w.setCenter(0.0f, 0.0f);
    torre_w.setSize(1, 1);
   


    torre_b.setCenter(0, 0);
    torre_b.setSize(1, 1);
    

    estado = 0;
}

//Constructor de las torres blancas y negras
Torre::Torre(int _f, int _c, int _color) {
    torre_w.setCenter(0, 0);
    torre_w.setSize(1, 1);
    
    Vector pos1;
    posicion = pos1.conversor(_f, _c);

    torre_b.setCenter(0, 0);
    torre_b.setSize(1, 1);
   
    Vector pos2;
    posicion = pos2.conversor(_f, _c);
    color = _color;
    estado = 0;
    fc.setCasillas(_f, _c);
}

//Funcion para representar las torres
void Torre::dibuja() {

    posicion = posicion.conversor(fc.getF(), fc.getC());
    if (color == 0) {
        glPushMatrix();
        glTranslatef(posicion.getX(), posicion.getY(), 0.5);
        glColor3f(1.0f, 0.0f, 0.0f);
        torre_w.draw();
        glPopMatrix();
    }
    else {
        glPushMatrix();
        glTranslatef(posicion.getX(), posicion.getY(), 0.5);
        glColor3f(1.0f, 0.0f, 0.0f);
        torre_b.draw();
        glPopMatrix();
    }
}

//Funcion para saber que tipo de pieza es 
int Torre::getTipoPieza() {
    return 1;
}
