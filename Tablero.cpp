#include "freeglut.h"
#include "ETSIDI.h"
#include "Tablero.h"


//Dibujar tablero

void Tablero::dibuja() {

	//Pto. de vista de la camara
	gluLookAt(x_ojo, y_ojo, z_ojo,  // posicion del ojo
		0.0, 0.0, 0.0,    // hacia que punto mira  (0,0,0) 
		0.0, 0.0, 1.0);      // definimos hacia arriba (eje Z)    
