#include "CoordinadorAjedrez.h"

void coordinador::dibuja() {
	gluLookAt(15, 18, 48,    // ubicación inicial del ojo (perspectiva)
		15, 18, 0,			 // punto hacia el que mira el ojo
		0.0, 1.0, 0.0);      // orientación hacia el eje Y+ 

//ESTADOS
	switch(estado){
		case START:
			glEnable(GL_TEXTURE_2D);
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
			glDisable(GL_LIGHTING);
	
			glBegin(GL_POLYGON);
			glColor3f(1, 1, 1);
			
			//JUGAR CON LOS VÉRTICES HASTA ATINAR
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
			glEnable(GL_TEXTURE_2D);
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
				case GANA_BLANCAS:
			glEnable(GL_TEXTURE_2D);
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
			glEnable(GL_TEXTURE_2D);
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
		
	}
}




void coordinador::tecla(unsigned char key) {
	switch (estado)
	{
	
	case START:
		if (key == 'p' || key == 'P') {
			estado = MENU_1C1;
		}
		if (key == 'b' || key == 'B') {
			estado = MENU_BOT;	
		}
		break;
		
	case MENU_1C1:
		if (key == 'i' || key == 'I') {
			estado = INSTRUCC_1C1;
		}
		else if (key == ' ') {
			mundo.inicializa(0, 0);
			estado = RATON;
		}

		break;
	case INSTRUCC_1C1:
		if (key == 'i' || key == 'I') {
			estado = MENU_1C1;
		}
		break;

	case MENU_BOT:
		if (key == 'i' || key == 'I') {
			estado = INSTRUCC_BOT;
		}
		else if (key == ' ') {
			mundo.inicializa(0, 1);
			estado = RATON;
		}

		break;
	case INSTRUCC_BOT:
		if (key == 'i' || key == 'I') {
			estado = MENU_BOT;
		}
		break;
	

	
	case RATON:
		if (key == ' ') {
			estado = JUEGO;
		}
		break;

	case JUEGO:
		break;

	case GANA_BLANCAS:
		if (key == 'a' || key == 'A')
		{
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
