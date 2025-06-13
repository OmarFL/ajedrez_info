#include "freeglut.h"
#include "ETSIDI.h"
#include "Tablero.h"


//Constructor del tablero
Tablero::Tablero()
{
}


//Dibujar tablero

void Tablero::dibuja() {

	//Pto. de vista de la camara

	gluLookAt(x_ojo, y_ojo, z_ojo,  // posicion del ojo
		0.0, 0.0, 0.0,    // hacia que punto mira  (0,0,0) 
		0.0, 0.0, 1.0);      // definimos hacia arriba (eje Z)    

//Representacion del tablero

glClear(GL_COLOR_BUFFER_BIT);
	

	for (int columna = 1; columna <= 10; columna++) {
		for (int fila = 1; fila <= 8; fila++) {
			posicion.setX(columna * 1.5 - 6);
			posicion.setY(fila * 1.5 - 7.5);

			if (columna == selector.getFila() && fila == selector.getColumna()) {

				casillas[columna - 1][fila - 1].setColor(0, 255, 0);

			}
			else
			{
				if ((columna + fila) & 1)
				{
					casillas[columna - 1][fila - 1].setColor(255, 255, 255);
					casillas[columna - 1][fila - 1].setCasillas(columna, fila);
				}

				else
				{
					casillas[columna - 1][fila - 1].setColor(0, 0, 0);
					casillas[columna - 1][fila - 1].setCasillas(columna, fila);
				}
			}

			casillas[columna - 1][fila - 1].cuadrado(posicion.getX(), posicion.getY(), 1.5);
			posf[columna - 1] = posicion.getX();
			posc[fila - 1] = posicion.getY();

		}
	}
	 


