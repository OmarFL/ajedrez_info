#include "Peon.h"
#include "freeglut.h"

//Constructor de peon predeterminado
Peon::Peon()
{
	peon_w.setCenter(0, 0);
	peon_w.setSize(1, 1);

	peon_b.setCenter(0, 0);
	peon_b.setSize(1, 1);

}

/*Peon::~Peon()
{
	
}*/

//Constructor de los peones blancos y negros
Peon::Peon(int _f, int _c, int _color) {
	peon_w.setCenter(0, 0);
	peon_w.setSize(1, 1);
	Vector pos1;
	posicion = pos1.conversor(_f, _c);

	peon_b.setCenter(0, 0);
	peon_b.setSize(1, 1);
	Vector pos2;
	posicion = pos2.conversor(_f, _c);
	color = _color;
	fc.setCasillas(_f, _c);
}

//Funcion para representar los peones
void Peon::dibuja() { 
	// CALCULO DIRECTO DE COORDENADAS (sin usar conversor)
	float y = (fc.getC() - 1) * 1.5f - 6.45f; // Columnas [1-10] -> [-6.75, 7.5]
	float x = (fc.getF() - 1) *1.5f - 8.55f; // Filas [1-8] -> [-5.25, 6.0]

	glPushMatrix();
	glTranslatef(x, y, 0.5f);
	if (color == 0) peon_w.draw();
	else peon_b.draw();
	glPopMatrix();
}

//Funcion para saber que tipo de pieza es 
int Peon::getTipoPieza() {
	return 6;
}
