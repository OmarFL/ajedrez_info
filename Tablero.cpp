#include "freeglut.h"
#include "ETSIDI.h"
#include "Tablero.h"


//Dibujar tablero

void Tablero::dibuja()
{

	//GESTIÓN DE LAS CASILLAS:
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 10; j++) {
			glBegin(GL_POLYGON);
			if (posicion_selecc >= 0 &&
				piezas[posicion_selecc]->Get_Posicion().x == i &&
				piezas[posicion_selecc]->Get_Posicion().y == j) {
				// Resaltado según color de la pieza
				if (piezas[posicion_selecc]->Get_Valor() > 0) { // Pieza blanca
					glColor3ub(143, 245, 244); // Azul claro para las blancas
				}
				else { // Pieza negra
					glColor3ub(241, 137, 113); // Rojo claro para las negras
				}
			}
			else {
				// Color normal de la casilla
				glColor3ub(Casillero[i][j].colorR, Casillero[i][j].colorG, Casillero[i][j].colorB);
			}
			glVertex3f(Casillero[i][j].param_x - 9, Casillero[i][j].param_y, 0.0f);
			glVertex3f(Casillero[i][j].param_x - 9, Casillero[i][j].param_y + 4, 0.0f);
			glVertex3f(Casillero[i][j].param_x - 5, Casillero[i][j].param_y + 4, 0.0f);
			glVertex3f(Casillero[i][j].param_x - 5, Casillero[i][j].param_y, 0.0f);
			glEnd();
			glLineWidth(1.0f);
		}
	}

	// GESTIÓN DEL BACKGROUND:

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D,
		ETSIDI::getTexture("imagenes/FONDO.png").id);
	glDisable(GL_LIGHTING);
	glBegin(GL_POLYGON);
	glColor3f(1, 1, 1);
	glTexCoord2d(0, 0); glVertex2d(-15, 41); //Esquina izquierda superior
	glTexCoord2d(0, 1); glVertex2d(-15, -4.5); //Esquina izquierda inferior
	glTexCoord2d(1, 1); glVertex2d(44.75, -4.5); //Esquina derecha inferior
	glTexCoord2d(1, 0); glVertex2d(44.75, 41); //Esquina derecha superior
	glEnd();
	glEnable(GL_LIGHTING);
	glDisable(GL_TEXTURE_2D);



	// GESTIÓN DE LOS MOVIMIENTOS POSIBLES
	DibujarMovimientosPosibles();



	// GESTIÓN DE TODAS LAS PIEZAS:
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 10; j++) {
			if (matriz[i][j] == -REY) {
				ETSIDI::Sprite sprite = { "imagenes/rey_b.png" };
				glPushMatrix();
				glTranslatef(Posic_Casillas[i][j].x - 10.1f, Posic_Casillas[i][j].y - 1.3f, 1);
				sprite.setSize(3.3, 3.3);
				sprite.draw();
				glPopMatrix();
			}
			if (matriz[i][j] == -DAMA) {
				ETSIDI::Sprite sprite = { "imagenes/dama_b.png" };
				glPushMatrix();
				glTranslatef(Posic_Casillas[i][j].x - 10.1f, Posic_Casillas[i][j].y - 1.3f, 1);
				sprite.setSize(3.3, 3.3);
				sprite.draw();
				glPopMatrix();
			}
			if (matriz[i][j] == -ALFIL) {
				ETSIDI::Sprite sprite = { "imagenes/alfil_b.png" };
				glPushMatrix();
				glTranslatef(Posic_Casillas[i][j].x - 10.0f, Posic_Casillas[i][j].y - 1.3f, 1);
				sprite.setSize(3.15, 3.15);
				sprite.draw();
				glPopMatrix();
			}
			if (matriz[i][j] == -CABALLO) {
				ETSIDI::Sprite sprite = { "imagenes/caballo_b.png" };
				glPushMatrix();
				glTranslatef(Posic_Casillas[i][j].x - 10.1f, Posic_Casillas[i][j].y - 1.3f, 1);
				sprite.setSize(3.3, 3.3);
				sprite.draw();
				glPopMatrix();
			}
			if (matriz[i][j] == -TORRE) {
				ETSIDI::Sprite sprite = { "imagenes/torre_b.png" };
				glPushMatrix();
				glTranslatef(Posic_Casillas[i][j].x - 10.0f, Posic_Casillas[i][j].y - 1.3f, 1);
				sprite.setSize(3.3, 3.3);
				sprite.draw();
				glPopMatrix();
			}
			if (matriz[i][j] == -PEON) {
				ETSIDI::Sprite sprite = { "imagenes/peon_b.png" };
				glPushMatrix();
				glTranslatef(Posic_Casillas[i][j].x - 10.1f, Posic_Casillas[i][j].y - 1.3f, 1);
				sprite.setSize(3.3, 3.3);
				sprite.draw();
				glPopMatrix();
			}
			if (matriz[i][j] == -CANCILLER) {
				ETSIDI::Sprite sprite = { "imagenes/canciller_b.png" };
				glPushMatrix();
				glTranslatef(Posic_Casillas[i][j].x - 11.1f, Posic_Casillas[i][j].y - 1.85f, 1);
				sprite.setSize(5.2, 4.5);
				sprite.draw();
				glPopMatrix();
			}
			if (matriz[i][j] == -ARZOBISPO) {
				ETSIDI::Sprite sprite = { "imagenes/arzobispo_b.png" };
				glPushMatrix();
				glTranslatef(Posic_Casillas[i][j].x - 10.0f, Posic_Casillas[i][j].y - 1.3f, 1);
				sprite.setSize(3.3, 3.3);
				sprite.draw();
				glPopMatrix();
			}
			if (matriz[i][j] == REY) {
				ETSIDI::Sprite sprite = { "imagenes/rey_w.png" };
				glPushMatrix();
				glTranslatef(Posic_Casillas[i][j].x - 10.1f, Posic_Casillas[i][j].y - 0.9f, 1);
				sprite.setSize(3.5, 3.5);
				sprite.draw();
				glPopMatrix();
			}
			if (matriz[i][j] == DAMA) {
				ETSIDI::Sprite sprite = { "imagenes/dama_w.png" };
				glPushMatrix();
				glTranslatef(Posic_Casillas[i][j].x - 10.1f, Posic_Casillas[i][j].y - 0.9f, 1);
				sprite.setSize(3.3, 3.3);
				sprite.draw();
				glPopMatrix();
			}
			if (matriz[i][j] == ALFIL) {
				ETSIDI::Sprite sprite = { "imagenes/alfil_w.png" };
				glPushMatrix();
				glTranslatef(Posic_Casillas[i][j].x - 10.1f, Posic_Casillas[i][j].y - 0.9f, 1);
				sprite.setSize(3.3, 3.3);
				sprite.draw();
				glPopMatrix();
			}
			if (matriz[i][j] == CABALLO) {
				ETSIDI::Sprite sprite = { "imagenes/caballo_w.png" };
				glPushMatrix();
				glTranslatef(Posic_Casillas[i][j].x - 10.1f, Posic_Casillas[i][j].y - 0.9f, 1);
				sprite.setSize(3.3, 3.3);
				sprite.draw();
				glPopMatrix();
			}
			if (matriz[i][j] == TORRE) {
				ETSIDI::Sprite sprite = { "imagenes/torre_w.png" };
				glPushMatrix();
				glTranslatef(Posic_Casillas[i][j].x - 10.1f, Posic_Casillas[i][j].y - 0.9f, 1);
				sprite.setSize(3.3, 3.3);
				sprite.draw();
				glPopMatrix();
			}
			if (matriz[i][j] == PEON) {
				ETSIDI::Sprite sprite = { "imagenes/peon_w.png" };
				glPushMatrix();
				glTranslatef(Posic_Casillas[i][j].x - 10.1f, Posic_Casillas[i][j].y - 1.1f, 1);
				sprite.setSize(3.3, 3.3);
				sprite.draw();
				glPopMatrix();
			}
			if (matriz[i][j] == CANCILLER) {
				ETSIDI::Sprite sprite = { "imagenes/canciller_w.png" };
				glPushMatrix();
				glTranslatef(Posic_Casillas[i][j].x - 10.1f, Posic_Casillas[i][j].y - 0.9f, 1);
				sprite.setSize(3.3, 3.3);
				sprite.draw();
				glPopMatrix();
			}
			if (matriz[i][j] == ARZOBISPO) {
				ETSIDI::Sprite sprite = { "imagenes/arzobispo_w.png" };
				glPushMatrix();
				glTranslatef(Posic_Casillas[i][j].x - 10.5f, Posic_Casillas[i][j].y - 0.6f, 1);
				sprite.setSize(4.0, 4.0);
				sprite.draw();
				glPopMatrix();
			}

		}
	}

}



// Selecciona una pieza en la posición del ratón para moverla
void Tablero::Seleccionar_Pieza_1VS1(Vector origen) 
{
	posicion_selecc = -1;	  // Resetear selección previa

	if (matriz[origen.x][origen.y] != 0) {	
		// Si hay pieza en la casilla, se busca la pieza en el vector de piezas

		for (int z = 0; z < static_cast<int>(piezas.size()); z++) {
			if (piezas[z]->Get_Posicion().x == origen.x && piezas[z]->Get_Posicion().y == origen.y) {
				posicion_selecc = z;
				break;
			}
		}

		//Si la pieza no corresponde con el color del turno
		if (posicion_selecc != -1) {
			// Verificar turno correcto (valor negativo = negras, positivo = blancas)
			if ((color && piezas[posicion_selecc]->Get_Valor() < 0) || (!color && piezas[posicion_selecc]->Get_Valor() > 0)) { 
				posicion_selecc = -1;			
			}

			if (posicion_selecc != -1) {
				pos_x = origen.x;
				pos_y = origen.y;
				CalcularMovimientosPosibles();
			}
		}
	}
}



void Tablero::Mover_Pieza_1VS1(Vector destino) //posición del ratón -> destino
{

	if (posicion_selecc != -1) { // Si es una casilla permitida

		//Deshabilitación de las limitaciones de movimiento
		if (Selec_Mover(destino.x, destino.y, true)) { 

			// Algoritmo de comer: se elimina la pieza si hay otra del oponente en el destino
			if ((color && matriz[destino.x][destino.y] != 0) || (!color && matriz[destino.x][destino.y] != 0)) {

				for (int z = 0; z < static_cast<int>(piezas.size()); z++) {
					if (piezas[z]->Get_Posicion().x == destino.x && piezas[z]->Get_Posicion().y == destino.y) {

						delete piezas[z];
						if (z < posicion_selecc) posicion_selecc--;
						piezas.erase(piezas.begin() + z);
					}
				}

			}


			piezas[posicion_selecc]->Set_Posicion(destino.x, destino.y);

			//Actualización de los valores
			matriz[destino.x][destino.y] = matriz[pos_x][pos_y];
			matriz[pos_x][pos_y] = 0;

			//Cambio de turno
			if (color) color = false;		// Turno de las Negras
			else color = true;			// Turno de las Blancas

			

		}
		
	posicion_selecc = -1;
	movimientos_posibles.clear(); // Limpiar movimientos posibles
}
