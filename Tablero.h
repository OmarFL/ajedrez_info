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

	// Variables de estado del juego
	int mov_x_IA = -1, mov_y_IA = -1;      // Movimiento planeado por la IA
	int posicion_selecc = -1;               // Índice de pieza seleccionada (-1=nada)
	int pos_x = -1, pos_y = -1;            // Posición de pieza seleccionada (jugador)
	int pos_x_IA = 0, pos_y_IA = 0;        // Posición de pieza seleccionada (IA)
	bool color = true;                      // Turno (true=blancas, false=negras)

	bool jaqblancas = false;               // Rey blanco en jaque
	bool jaqmateblancas = false;           // Rey blanco en jaque mate
	bool jaqnegras = false;                // Rey negro en jaque
	bool jaqmatenegras = false;            // Rey negro en jaque mate
	bool tablas = false;                   // Estado de empate
        //enroque
        bool enroqueLargoBlancas = true;
        bool enroqueCortoBlancas = true;
        bool enroqueLargoNegras = true;
        bool enroqueCortoNegras = true;
        bool torreReyBlancas = true; 
        bool torreDamaBlancas = true;
        bool torreReyNegras = true;   
        bool torreDamaNegras = true;    
	// Colores para interfaz
	int colorR, colorG, colorB;            // Color indicador de turno
	int colorJR, colorJG, colorJB;         // Color para resaltar jugadas

	// Tipos de piezas
	enum { REY = 1, DAMA, ALFIL, CABALLO, TORRE, PEON, ARZOBISPO, CANCILLER };

	//Variables para la implementación del marcador
	float marcador_x, marcador_y, marcador_ancho, marcador_alto;
	int marcador_colorR, marcador_colorG, marcador_colorB;


public:
	void dibuja();
	void DibujarMarcadorTurno();

	void Seleccionar_Pieza_1VS1(Vector origen);  // Selecciona pieza en coordenadas
	void Mover_Pieza_1VS1(Vector destino);       // Mueve pieza a coordenadas

	void inicializa(const int& tipojuego); // Inicializa tablero según modo de juego
	void Auto_Mov();  					   // Ejecuta movimiento automático de IA (modo fácil)
	void Auto_Mov_Medio();				   // Dificultad media de la IA
	void Auto_Mov_Dificil();			   // Dificultad difícil de la IA	
	
	void CalcularMovimientosPosibles(); 
	void DibujarMovimientosPosibles();  // Método para dibujar las casillas a las que es posible moverse


	// Lógica de movimientos por tipo de pieza
	bool Selec_Peon(int, int);            // Valida movimiento de peón
	bool Selec_Rey(int, int);             // Valida movimiento de rey
	bool Selec_Alfil(int, int);           // Valida movimiento de alfil
	bool Selec_Dama(int, int);            // Valida movimiento de dama
	bool Selec_Torre(int, int);           // Valida movimiento de torre
	bool Selec_Caballo(int, int);         // Valida movimiento de caballo
	bool Selec_Arzobispo(int, int);       // Valida movimiento de arzobispo
	bool Selec_Canciller(int, int);       // Valida movimiento de canciller
//Enroque
bool Selec_Enroque(int i, int j);
void RealizarEnroque(bool esCorto);
	// Lógica del juego
	bool color_check(int R, int G, int B); // Verifica color de casilla
	bool Consultar_Turno();               // Devuelve turno actual
	void Coronar(int, int, int, Vector);  // Maneja coronación de peones
	bool Jaque(bool col);                 // Comprueba jaque para un color
	void Comprobar_Jaque();               // Detecta situaciones de jaque
	void Comprobar_JaqueMate();           // Detecta jaque mate

	// Getters y setters
	void Set_Oponente(const int& TIPO_OPON) { tipo_oponente = TIPO_OPON; }
	int Get_Oponente() { return tipo_oponente; }

	// Estados de juego
	bool Get_JaqueBlancas() { 
		return jaqblancas; 
	}

	bool Get_JaqueMateBlancas() {
		if (jaqmateblancas && jaqblancas)
			return true;
		return false;
	}

	bool Get_JaqueNegras() { 
		return jaqnegras; 
	}

	bool Get_JaqueMateNegras() {
		if (jaqmatenegras && jaqnegras)
			return true;
		return false;
	}

	bool Get_Tablas() { 
		return tablas; 
	}

	// Dificultad IA
	void setDificultadIA(int dificultad);
	void RealizarMovimientoIA(int mov_x, int mov_y, int pos_sel);

	void Borrar();

	
	friend class Mundo;	  
	friend class IA_Movimientos;
};
