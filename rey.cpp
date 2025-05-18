#include "rey.h"
#include "freeglut.h"

Rey::Rey()
{
	rey_w.setCenter(0, 0);
	rey_w.setSize(1, 1);

	rey_b.setCenter(0, 0);
	rey_b.setSize(1, 1);

}

//Constructor de los reyes blanco y negro
Rey::Rey(int _f, int _c, int _color) {
	rey_w.setCenter(0, 0);
	rey_w.setSize(1, 1);
	Vector pos1;
	posicion = pos1.conversor(_f, _c);

	rey_b.setCenter(0, 0);
	rey_b.setSize(1, 1);
	Vector pos2;
	posicion = pos2.conversor(_f, _c);
	color = _color;
	fc.setCasillas(_f, _c);
}

//Funcion para representar los reyes
void Rey::dibuja() {
	// CALCULO DIRECTO DE COORDENADAS (sin usar conversor)
	float y = (fc.getC() - 1) * 1.5f - 6.45f; // Columnas [1-10] -> [-6.75, 7.5]
	float x = (fc.getF() - 1) * 1.5f - 8.55f; // Filas [1-8] -> [-5.25, 6.0]

	glPushMatrix();
	glTranslatef(x, y, 0.5f);
	if (color == 0) rey_w.draw();
	else rey_b.draw();
	glPopMatrix();
}

//Funcion para saber que tipo de pieza es 
int Rey::getTipoPieza() {
	return 5;
}
