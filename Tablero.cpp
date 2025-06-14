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
