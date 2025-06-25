#include "mundo.h"
#include <iostream>
#include <vector>
#include "freeglut.h"
#include <ETSIDI.h>
#include "Tablero.h"
#include "Pieza.h"
#include <thread>  
#include <chrono>  

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



void Mundo::Boton_Raton(int num_rival, int x, int y, int boton, bool abajo, bool espacio, bool ref_tecla) 
{

        // Verificamos si el clic fue dentro del tablero o es turno de la IA
        if ((posY >= -300 && posY <= 144 && posX >= -300 && posX <= 144) ||
            ((!tablero.Consultar_Turno()) && num_rival == 1)) {

            // Modo 1vs1 (humano vs humano)
            if (num_rival == 0) {
                if (boton == GLUT_LEFT_BUTTON) {
                    // Selección de pieza con clic izquierdo
                    Casilla_ini.x = (int)((posY / casillas_ancho));
                    Casilla_ini.y = (int)((posX / casillas_ancho) + 2);
                    tablero.Seleccionar_Pieza_1VS1(Casilla_ini);
                }

                if (boton == GLUT_RIGHT_BUTTON) {
                    // Movimiento de pieza con clic derecho
                    Casilla_fin.x = (int)(posY / casillas_ancho);
                    Casilla_fin.y = (int)((posX / casillas_ancho) + 2);
                    tablero.Mover_Pieza_1VS1(Casilla_fin);
                }
            }

            // Modo contra IA
            if (num_rival == 1) {
                // Solo procesar si es turno del jugador humano
                if (tablero.Consultar_Turno() == true) {
                    if (boton == GLUT_LEFT_BUTTON) {
                        // Selección de pieza
                        Casilla_ini.x = (int)(posY / casillas_ancho);
                        Casilla_ini.y = (int)((posX / casillas_ancho) + 2);
                        tablero.Seleccionar_Pieza_1VS1(Casilla_ini);
                    }

                    if (boton == GLUT_RIGHT_BUTTON) {
                        // Movimiento de pieza
                        Casilla_fin.x = (int)(posY / casillas_ancho);
                        Casilla_fin.y = (int)((posX / casillas_ancho) + 2);
                        tablero.Mover_Pieza_1VS1(Casilla_fin);
                    }
                }
            }
        }
    }
