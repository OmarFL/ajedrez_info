#pragma once
#include "Tablero.h"
#include "ETSIDI.h"


class coordinador {
    Mundo mundo;        // Objeto que representa el mundo/entorno del juego
    
public:

    void dibuja();      // Método para renderizar/dibujar el juego
    void tecla(unsigned char key);  // Maneja eventos de teclado
    void Boton_Raton(int num_rival, int x, int y, int boton, bool abajo, bool espacio, bool ref_tecla);  // Maneja eventos del ratón

};
