#include "Vector.h"

//Constuctor de vector
Vector::Vector(float _x,float _y)
{
	x = _x;
	y = _y;
}

//Funcion de conversion de la posicion de la casilla a las coordenadas del plano XY que esta representado el tablero
Vector Vector::conversor(int _f, int _c) {

	Vector resultado;
	switch (_f) {

    case 1:
        resultado.x = -9.9;
        break;
    case 2:
        resultado.x = -8.45;
        break;
    case 3:
        resultado.x = -7;
        break;
    case 4:
        resultado.x = -5.55;
        break;
    case 5:
        resultado.x = -4.05;
        break;
    case 6:
        resultado.x = -2.55;
        break;
    case 7:
        resultado.x = -1.15;
        break;
    case 8:
        resultado.x = 0.35;
        break;
    case 9:
        resultado.x = 1.85;
        break;
    case 10:
        resultado.x = 3.35;
        break;
    case 11:
        resultado.x = 20;
        break;
    }

	switch (_c) {

	case 1:
		resultado.y = -6.4;
		break;
	case 2:
		resultado.y = -4.85;
		break;
	case 3:
		resultado.y = -3.35;
		break;
	case 4:
		resultado.y = -1.9;
		break;
	case 5:
		resultado.y = -0.45;
		break;
	case 6:
		resultado.y = 1;
		break;
	case 7:
		resultado.y = 2.35;
		break;
	case 8:
		resultado.y = 3.85;
		break;

	}

	return resultado;
}
