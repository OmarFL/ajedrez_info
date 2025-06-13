#include "Mundo.h"
#include <iostream>

using namespace std;

void Mundo::dibuja()
{
	// Delegamos el dibujado al tablero que contiene las piezas
	tablero.dibuja();

}

void Mundo::inicializa(int tipo_juego, const int& num_rival)
{
	tablero.inicializa(tipo_juego);  // Prepara el tablero según el modo de juego
	tablero.Set_Oponente(num_rival); // Establece el tipo de oponente
}
