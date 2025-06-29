#include "CoordinadorAjedrez.h"

void coordinador::dibuja() {
	// Gestión de la música de fondo
if (!musicaJuegoActiva && !musicaMenuActiva) {
	ETSIDI::playMusica("sonidos/MusicaFondo.wav", true);
	musicaMenuActiva = true;
}

// Soundtracks distintos en la interfaz de inicio y durante el gameplay
if (estado == JUEGO && !musicaJuegoActiva) {
	ETSIDI::stopMusica();
	ETSIDI::playMusica("sonidos/gameplay.mp3", true);
	musicaJuegoActiva = true;
	musicaMenuActiva = false;
}
else if (estado != JUEGO && !musicaMenuActiva) {
	ETSIDI::stopMusica();
	ETSIDI::playMusica("sonidos/MusicaFondo.wav", true);
	musicaMenuActiva = true;
	musicaJuegoActiva = false;
}
	gluLookAt(15, 18, 48,    // ubicación inicial del ojo (perspectiva)
		15, 18, 0,			 // punto hacia el que mira el ojo
		0.0, 1.0, 0.0);      // orientación hacia el eje Y+ 
	switch (estado)
	{
	
	case START:

		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D,
			ETSIDI::getTexture("imagenes/pantalla_principal.png").id);
		glDisable(GL_LIGHTING);
		glBegin(GL_POLYGON);
		glColor3f(1, 1, 1);
		glTexCoord2d(0, 0); glVertex2d(-15, 41); //Esquina izquierda superior
		glTexCoord2d(0, 1); glVertex2d(-15, -4.5); //Esquina izquierda inferior
		glTexCoord2d(1, 1); glVertex2d(45, -4.5); //Esquina derecha inferior
		glTexCoord2d(1, 0); glVertex2d(45, 41); //Esquina derecha superior
		glEnd();
		glEnable(GL_LIGHTING);
		glDisable(GL_TEXTURE_2D);
		break;


	case MENU_1C1:
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D,
			ETSIDI::getTexture("imagenes/pvp_menu.png").id);
		glDisable(GL_LIGHTING);
		glBegin(GL_POLYGON);
		glColor3f(1, 1, 1);
		glTexCoord2d(0, 0); glVertex2d(-15, 41); //Esquina izquierda superior
		glTexCoord2d(0, 1); glVertex2d(-15, -4.5); //Esquina izquierda inferior
		glTexCoord2d(1, 1); glVertex2d(45, -4.5); //Esquina derecha inferior
		glTexCoord2d(1, 0); glVertex2d(45, 41); //Esquina derecha superior
		glEnd();
		glEnable(GL_LIGHTING);
		glDisable(GL_TEXTURE_2D);
		break;


	case INSTRUCC_1C1:

		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D,
			ETSIDI::getTexture("imagenes/pvp_intrucciones.png").id);
		glDisable(GL_LIGHTING);
		glBegin(GL_POLYGON);
		glColor3f(1, 1, 1);
		glTexCoord2d(0, 0); glVertex2d(-15, 41); //Esquina izquierda superior
		glTexCoord2d(0, 1); glVertex2d(-15, -4.5); //Esquina izquierda inferior
		glTexCoord2d(1, 1); glVertex2d(45, -4.5); //Esquina derecha inferior
		glTexCoord2d(1, 0); glVertex2d(45, 41); //Esquina derecha superior
		glEnd();
		glEnable(GL_LIGHTING);
		glDisable(GL_TEXTURE_2D);
		break;

	
	case MENU_BOT:

		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D,
			ETSIDI::getTexture("imagenes/bot_menu.png").id);
		glDisable(GL_LIGHTING);
		glBegin(GL_POLYGON);
		glColor3f(1, 1, 1);
		glTexCoord2d(0, 0); glVertex2d(-15, 41); //Esquina izquierda superior
		glTexCoord2d(0, 1); glVertex2d(-15, -4.5); //Esquina izquierda inferior
		glTexCoord2d(1, 1); glVertex2d(45, -4.5); //Esquina derecha inferior
		glTexCoord2d(1, 0); glVertex2d(45, 41); //Esquina derecha superior
		glEnd();
		glEnable(GL_LIGHTING);
		glDisable(GL_TEXTURE_2D);
		break;


	case INSTRUCC_BOT:

		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D,
			ETSIDI::getTexture("imagenes/bot_instrucciones.png").id);
		glDisable(GL_LIGHTING);
		glBegin(GL_POLYGON);
		glColor3f(1, 1, 1);
		glTexCoord2d(0, 0); glVertex2d(-15, 41); //Esquina izquierda superior
		glTexCoord2d(0, 1); glVertex2d(-15, -4.5); //Esquina izquierda inferior
		glTexCoord2d(1, 1); glVertex2d(45, -4.5); //Esquina derecha inferior
		glTexCoord2d(1, 0); glVertex2d(45, 41); //Esquina derecha superior
		glEnd();
		glEnable(GL_LIGHTING);
		glDisable(GL_TEXTURE_2D);
		break;

	
	case RATON:
		
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D,
			ETSIDI::getTexture("imagenes/jugabilidad.png").id);
		glDisable(GL_LIGHTING);
		glBegin(GL_POLYGON);
		glColor3f(1, 1, 1);
		glTexCoord2d(0, 0); glVertex2d(-15, 41); //Esquina izquierda superior
		glTexCoord2d(0, 1); glVertex2d(-15, -4.5); //Esquina izquierda inferior
		glTexCoord2d(1, 1); glVertex2d(45, -4.5); //Esquina derecha inferior
		glTexCoord2d(1, 0); glVertex2d(45, 41); //Esquina derecha superior
		glEnd();
		glEnable(GL_LIGHTING);
		glDisable(GL_TEXTURE_2D);
		break;


	case JUEGO:

		mundo.dibuja();

		if (mundo.get_Jaques() != 0) {

			mundo.borrar();

			switch (mundo.get_Jaques()) {
			case 1:
				estado = GANA_NEGRAS;
				break;
			case 2:
				estado = GANA_BLANCAS;
				break;
			case 3:
				estado = TABLAS;
				break;
			}
		}

		break;

	default:
		break;


	case GANA_BLANCAS:
		ETSIDI::play("sonidos/Victoria.wav");
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D,
			ETSIDI::getTexture("imagenes/gana_blancas.png").id);
		glDisable(GL_LIGHTING);
		glBegin(GL_POLYGON);
		glColor3f(1, 1, 1);
		glTexCoord2d(0, 0); glVertex2d(-15, 41); //Esquina izquierda superior
		glTexCoord2d(0, 1); glVertex2d(-15, -4.5); //Esquina izquierda inferior
		glTexCoord2d(1, 1); glVertex2d(45, -4.5); //Esquina derecha inferior
		glTexCoord2d(1, 0); glVertex2d(45, 41); //Esquina derecha superior
		glEnd();
		glEnable(GL_LIGHTING);
		glDisable(GL_TEXTURE_2D);
		break;


	case GANA_NEGRAS:
		ETSIDI::play("sonidos/Derrota.wav");
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D,
			ETSIDI::getTexture("imagenes/gana_negras.png").id);
		glDisable(GL_LIGHTING);
		glBegin(GL_POLYGON);
		glColor3f(1, 1, 1);
		glTexCoord2d(0, 0); glVertex2d(-15, 41); //Esquina izquierda superior
		glTexCoord2d(0, 1); glVertex2d(-15, -4.5); //Esquina izquierda inferior
		glTexCoord2d(1, 1); glVertex2d(45, -4.5); //Esquina derecha inferior
		glTexCoord2d(1, 0); glVertex2d(45, 41); //Esquina derecha superior
		glEnd();
		glEnable(GL_LIGHTING);
		glDisable(GL_TEXTURE_2D);
		break;


	case TABLAS:
		ETSIDI::play("sonidos/tablas.wav");
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D,
			ETSIDI::getTexture("imagenes/tablas_.png").id);
		glDisable(GL_LIGHTING);
		glBegin(GL_POLYGON);
		glColor3f(1, 1, 1);
		glTexCoord2d(0, 0); glVertex2d(-15, 41); //Esquina izquierda superior
		glTexCoord2d(0, 1); glVertex2d(-15, -4.5); //Esquina izquierda inferior
		glTexCoord2d(1, 1); glVertex2d(45, -4.5); //Esquina derecha inferior
		glTexCoord2d(1, 0); glVertex2d(45, 41); //Esquina derecha superior
		glEnd();
		glEnable(GL_LIGHTING);
		glDisable(GL_TEXTURE_2D);
		break;
	}
}




void coordinador::tecla(unsigned char key) {
	switch (estado)
	{
	
	case START:
		if (key == 'p' || key == 'P') {
			estado = MENU_1C1;
			ETSIDI::play("sonidos/Seleccion.wav");
		}
		if (key == 'b' || key == 'B') {
			estado = MENU_BOT;
			ETSIDI::play("sonidos/Seleccion.wav");
		}
		break;
		
	case MENU_1C1:
		if (key == 'i' || key == 'I') {
			estado = INSTRUCC_1C1;
			ETSIDI::play("sonidos/Seleccion.wav");
		}
		else if (key == ' ') {
			mundo.inicializa(0, 0);
			estado = RATON;
			ETSIDI::play("sonidos/Seleccion.wav");
		}

		break;
	case INSTRUCC_1C1:
		if (key == 'i' || key == 'I') {
			ETSIDI::play("sonidos/Seleccion.wav");
			estado = MENU_1C1;
		}
		break;

	case MENU_BOT:
		if (key == 'i' || key == 'I') {
			estado = INSTRUCC_BOT;
			ETSIDI::play("sonidos/Seleccion.wav");
		}
		else if (key == ' ') {
			mundo.inicializa(0, 1);
			estado = RATON;
			ETSIDI::play("sonidos/Seleccion.wav");
		}

		break;
	case INSTRUCC_BOT:
		if (key == 'i' || key == 'I') {
			ETSIDI::play("sonidos/Seleccion.wav");
			estado = MENU_BOT;
		}
		break;
	

	
	case RATON:
		if (key == ' ') {

			ETSIDI::play("sonidos/Seleccion.wav");
			estado = JUEGO;
		}
		break;

	case JUEGO:
		break;

	case GANA_BLANCAS:
		if (key == 'a' || key == 'A')
		{
			ETSIDI::play("sonidos/Seleccion.wav");
			estado = START;
		}
		if (key == 'q' || key == 'Q')
		{
			exit(0);
		}
		break;

	case GANA_NEGRAS:
		if (key == 'a' || key == 'A')
		{
			ETSIDI::play("sonidos/Seleccion.wav");
			estado = START;
		}
		if (key == 'q' || key == 'Q')
		{
			exit(0);
		}
		break;
	
	case TABLAS:
		if (key == 'a' || key == 'A')
		{
			ETSIDI::play("sonidos/Seleccion.wav");
			estado = START;
		}
		if (key == 'q' || key == 'Q')
		{
			exit(0);
		}
		break;

	default:
		break;
	}
}


void coordinador::Boton_Raton(int num_rival, int x, int y, int boton, bool abajo, bool espacio, bool ref_tecla) {
	num_rival = mundo.get_opon();
	if (estado == 0)mundo.Boton_Raton(num_rival, x, y, boton, abajo, espacio, ref_tecla);
}
