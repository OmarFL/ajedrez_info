#pragma once
#include "Vector.h"
#include <ETSIDI.h>

class Pieza
{
	int valor;              // Valor numérico de la pieza (para lógica de juego/IA)
	Vector posicion_selecc; // Posición actual de la pieza en el tablero (coordenadas)

public:
	//Constructor
	Pieza(int x, int y, int val);	 

	void Set_Posicion(int, int);	//Establece una nueva posición para la pieza

	Vector Get_Posicion();			//Obtiene la posición actual de la pieza

	int Get_Valor();				//Obtiene el valor asignado a la pieza
	void Cambiar_Valor(int);		//Recibe un entero que indica el nuevo valor a asignar

};
