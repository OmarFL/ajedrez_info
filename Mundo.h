#pragma once
#include "Vector.h"
#include "Tablero.h"

using namespace std;


class Mundo
{
	Tablero tablero;               // Gestión del tablero y piezas
	Vector Posic_Casillas[8][10];  // Matriz para posiciones gráficas de las casillas
	int tipo_juego = 0;            // Almacena el modo de juego (1vs1, vsIA, etc.)
	int tipo_oponente = 0;         // Dificultad del oponente (si es IA)

public:

	void inicializa(int tipo_juego, const int& num_rival);
	void dibuja();
}
