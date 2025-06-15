#include "Pieza.h"

Pieza::Pieza(int x, int y, int val):
	valor(val),
	posicion_selecc({ x, y })	
{}

Vector Pieza::Get_Posicion() {
	return posicion_selecc;
}

void Pieza::Set_Posicion(int x, int y) {
	posicion_selecc.x = x;
	posicion_selecc.y = y;
}
