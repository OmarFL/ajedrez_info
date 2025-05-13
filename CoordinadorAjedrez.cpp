#include "CoordinadorAjedrez.h"

//Construcctor del coordinador
CoordinadorAjedrez::CoordinadorAjedrez() {

	estado = INICIO;
	sprite1.setCenter(0, 0);
	sprite1.setSize(12, 7);
	sprite2.setCenter(0, 0);
	sprite2.setSize(12, 7);
	sprite3.setCenter(0, 0);
	sprite3.setSize(12, 7);
	fin = 0; 
}

//Destructor del coordinador
CoordinadorAjedrez::~CoordinadorAjedrez() {

}

//Funcion para representar las pantallas de los diferentes estados
void CoordinadorAjedrez::dibuja() {

	if (estado == INICIO)
	{
		//CODIGO PARA PINTAR UNA PANTALLA NEGRA CON LETRAS
		gluLookAt(0, 7.5, 30, // posicion del ojo
			0.0, 7.5, 0.0, // hacia que punto mira (0,7.5,0)
			0.0, 1.0, 0.0); // definimos hacia arriba (eje Y)
		ETSIDI::setTextColor(1, 1, 0);
		ETSIDI::setFont("fuentes/Bitwise.ttf", 16);
		ETSIDI::printxy("Ajedrez informatica", -5, 13);
		ETSIDI::setTextColor(1, 1, 1);
		ETSIDI::setFont("fuentes/Bitwise.ttf", 12);
		ETSIDI::printxy("PULSE LA TECLA -E- PARA EMPEZAR", -5, 11);
		ETSIDI::printxy("PULSE LA TECLA -S- PARA SALIR", -5, 10);
		ETSIDI::printxy("Ajedrez UPM", -1, -1);

		glPushMatrix();
		glTranslatef(-10,1, 0.5);
		glColor3f(1.0f, 0.0f, 0.0f);
		sprite1.draw();
		glPopMatrix();
		
	}
}