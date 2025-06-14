#pragma once
#include <iostream>
#include <vector>
#include "ETSIDI.h"
#include "Pieza.h"
#include <Vector.h>



struct CasillA
{
	// Parámetros gráficos de casilla
	int param_x;
	int param_y;
	int colorR, colorG, colorB;
};

class Tablero
{
private:

	int tipo_juego;    // Modo de juego seleccionado
	int tipo_oponente; // 0=Humano, 1=IA

	CasillA Casillero[8][10];      // Almacena propiedades gráficas de cada casilla
	Vector Posic_Casillas[8][10];   // Posiciones centrales de las casillas para interacción
	std::vector<Vector> movimientos_posibles; // Almacena casillas destino posibles
	
	// Estructuras de datos del juego
	std::vector<std::vector<int>> matriz;  // Matriz lógica del tablero (8x10)
	std::vector<Pieza*> piezas;            // Vector de punteros a las piezas

public:
	void dibuja();

	void Seleccionar_Pieza_1VS1(Vector origen);  // Selecciona pieza en coordenadas
	void Mover_Pieza_1VS1(Vector destino);       // Mueve pieza a coordenadas

};