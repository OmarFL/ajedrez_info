#include "Pieza.h"
#include "freeglut.h"

/*
void Pieza::dibuja() {
	glColor3f(0.5f, 0.5f, 0.5f); // Color gris
	glutSolidCube(1.0);
}


void Pieza::setPos(int _f, int _c) {
	fc.setCasillas(_f, _c);
}

int Pieza::getTipoPieza() {
	return 0;
}

int Pieza::getColor() {
	return color;
}

int Pieza::getfila() {
	return fc.getF();
}

int Pieza::getcolumna() {
	return fc.getC();
}
*/

Casilla Pieza::getCasilla() {
	return fc;
}
