#include "Selector.h"
#include "freeglut.h"
#include <algorithm>

//Constructor del selector
Selector::Selector() {
	fila = 1;
	columna = 1;
}

//Funcion para inicializar el selector
void Selector::inicializa() {
	Selector selector;
}
//selector raton
void Selector::setPos(int _fila, int _columna) {
	fila = std::max(1, std::min(_fila, 10));    // Limita entre 1 y 10
	columna = std::max(1, std::min(_columna, 8)); // Limita entre 1 y 8
}
//Funcion para realizar el movimiento del selector por las casillas del tablero
void Selector::mover(unsigned char key) {
	switch (key)
	{
	case GLUT_KEY_LEFT:
		if (fila > 1)
			fila--;
		break;
	case GLUT_KEY_DOWN:
		if (columna > 1)
			columna--;
		break;
	case GLUT_KEY_RIGHT:
		if (fila < 10)
			fila++;
		break;
	case GLUT_KEY_UP:
		if (columna < 8)
			columna++;
		break;
	case 'A':
		if (fila > 1)
			fila--;
		break;
	case 'S':
		if (columna > 1)
			columna--;
		break;

	case 'W':
		if (columna < 8)
			columna++;
		break;
	case 'D':
		if (fila < 10)
			fila++;
		break;
	}
}

//Funcion que devuleve la fila
int Selector::getFila()
{
	return fila;
}

//Funcion que devuelve la columa
int Selector::getColumna()
{
	return columna;
}

//Funcion que devuelve el selector a su posicion incial
void Selector::reinicio() {
	fila = 1;
	columna = 1;
}
