#include "Casilla.h"
#include "freeglut.h"

//Constructor de casilla
Casilla::Casilla() {

	rojo = 255;
	verde = 255;
	azul = 255;
	fila = 0;
	columna = 0;
}

//Función para indicar la fila y columna de la casilla
void Casilla::setCasillas(int f, int c) {
	fila = f;
	columna = c;
}

//Función para indicar el color de la casilla
void Casilla::setColor(unsigned char r, unsigned char v, unsigned char a) {
	rojo = r;
	verde = v;
	azul = a;
}

//Función para representar una casilla
void Casilla::cuadrado(float _x, float _y, float tamanio) {

	tamanio /= 2;
	glBegin(GL_POLYGON);
	glColor3f(rojo, verde, azul);
	glVertex2f(_x + tamanio, _y + tamanio); glVertex2f(_x - tamanio, _y + tamanio);
	glVertex2f(_x - tamanio, _y - tamanio); glVertex2f(_x + tamanio, _y - tamanio);
	glEnd();
}
