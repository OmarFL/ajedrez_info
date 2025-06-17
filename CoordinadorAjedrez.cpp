#include "CoordinadorAjedrez.h"

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

