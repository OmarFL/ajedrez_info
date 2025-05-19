#include "arzobispo.h"
#include "freeglut.h"

//Constructor de arzobispo predeterminado
Arzobispo::Arzobispo()
{
    arzobispo_w.setCenter(0, 0);
    arzobispo_w.setSize(1, 1);


    arzobispo_b.setCenter(0, 0);
    arzobispo_b.setSize(1, 1);


    

}

//Constructor de los arzobispoes blancos y negros
Arzobispo::Arzobispo(int _f, int _c, int _color) {
    arzobispo_w.setCenter(0, 0);
    arzobispo_w.setSize(1, 1);

    Vector pos1;
    posicion = pos1.conversor(_f, _c);

    arzobispo_b.setCenter(0, 0);
    arzobispo_b.setSize(1, 1);

    Vector pos2;
    posicion = pos2.conversor(_f, _c);
    color = _color;
    estado = 0;
    fc.setCasillas(_f, _c);

}

//Funcion para representar los arzobispoes
void Arzobispo::dibuja() {

    posicion = posicion.conversor(fc.getF(), fc.getC());

    if (color == 0) {
        glPushMatrix();
        glTranslatef(posicion.getX(), posicion.getY(), 0.5);
        glColor3f(1.0f, 0.0f, 0.0f);
        arzobispo_w.draw();
        glPopMatrix();
    }
    else {
        glPushMatrix();
        glTranslatef(posicion.getX(), posicion.getY(), 0.5);
        glColor3f(1.0f, 0.0f, 0.0f);
        arzobispo_b.draw();
        glPopMatrix();
    }
}

//Funcion para saber que tipo de pieza es 
int Arzobispo::getTipoPieza() {
    return 7;

}
