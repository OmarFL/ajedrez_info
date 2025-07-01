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


	//---------------------Nota: NO cambiar el orden de dibujado bajo ningún concepto porque se lía parda xd---------------------
	
	// GESTIÓN DE LOS MOVIMIENTOS POSIBLES
	DibujarMovimientosPosibles();

	// GESTIÓN DEL MARCADOR
	DibujarMarcadorTurno();


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
//Enroque
bool Tablero::Selec_Enroque(int i, int j) {
	// Enroque corto (0-0)
	if (j > pos_y) {
		if (color) { // Blancas
			return enroqueCortoBlancas && torreReyBlancas &&
				matriz[0][5] == 0 && matriz[0][6] == 0 && matriz[0][7] == 0 && matriz[0][8] == 0 &&
				!Jaque(true);
		}
		else { // Negras
			return enroqueCortoNegras && torreReyNegras &&
				matriz[7][5] == 0 && matriz[7][6] == 0 && matriz[7][7] == 0 && matriz[7][8] == 0 &&
				!Jaque(false);
		}
	}
	// Enroque largo (0-0-0)
	else {
		if (color) { // Blancas
			return enroqueLargoBlancas && torreDamaBlancas &&
				matriz[0][3] == 0 && matriz[0][2] == 0 && matriz[0][1] == 0 &&
				!Jaque(true);
		}
		else { // Negras
			return enroqueLargoNegras && torreDamaNegras &&
				matriz[7][3] == 0 && matriz[7][2] == 0 && matriz[7][1] == 0 &&
				!Jaque(false);
		}
	}
}
void Tablero::RealizarEnroque(bool esCorto) {
	// Encontrar el rey y la torre correspondiente
	int reyIndex = -1, torreIndex = -1;
	int torreCol = esCorto ? 9 : 0; 

	for (int z = 0; z < piezas.size(); z++) {
		Vector pos = piezas[z]->Get_Posicion();
		// Buscar el rey
		if (pos.x == pos_x && pos.y == pos_y && abs(piezas[z]->Get_Valor()) == REY) {
			reyIndex = z;
		}
		// Buscar la torre
		else if (pos.x == pos_x && pos.y == torreCol && abs(piezas[z]->Get_Valor()) == TORRE) {
			torreIndex = z;
		}
	}

	if (reyIndex == -1 || torreIndex == -1) return;
	
	if (color) { // Blancas
		if (enroqueCortoBlancas == true && enroqueLargoBlancas == true) {
			if (esCorto) { // Enroque corto (0-0)
				// Mover torre 
				piezas[torreIndex]->Set_Posicion(pos_x, 7);
				matriz[0][7] = TORRE;
				matriz[0][9] = 0;
				// Mover rey
				piezas[reyIndex]->Set_Posicion(pos_x, 8);
				matriz[0][8] = REY;
				matriz[0][5] = 0;


			}
			else { // Enroque largo (0-0-0)
				// Mover torre (a1 -> d1)
				piezas[torreIndex]->Set_Posicion(pos_x, 2);
				matriz[0][2] = TORRE;
				matriz[0][0] = 0;
				// Mover rey (e1 -> a1)
				piezas[reyIndex]->Set_Posicion(pos_x, 1);
				matriz[0][1] = REY;
				matriz[0][5] = 0;


			}
			enroqueLargoBlancas = false; // Deshabilitar enroque largo para blancas
			enroqueCortoBlancas = false; // Deshabilitar enroque corto para blancas
		}
	}
	else { // Negras
		if (enroqueCortoNegras == true && enroqueLargoNegras == true) {

			if (esCorto) { // Enroque corto (0-0)
				// Mover rey (e8 -> h8)
				piezas[reyIndex]->Set_Posicion(pos_x, 8);
				matriz[7][8] = -REY;
				matriz[7][5] = 0;

				// Mover torre (h8 -> f8)
				piezas[torreIndex]->Set_Posicion(pos_x, 7);
				matriz[7][7] = -TORRE;
				matriz[7][9] = 0;
			}
			else { // Enroque largo (0-0-0)
				// Mover rey (e8 -> a8)
				piezas[reyIndex]->Set_Posicion(pos_x, 1);
				matriz[7][1] = -REY;
				matriz[7][5] = 0;

				// Mover torre (a8 -> d8)
				piezas[torreIndex]->Set_Posicion(pos_x, 2);
				matriz[7][2] = -TORRE;
				matriz[7][0] = 0;
			}
			enroqueLargoNegras = false; // Deshabilitar enroque largo para negras
			enroqueCortoNegras = false; // Deshabilitar enroque corto para negras
		}
	}

	// Reproducir sonido y actualizar estado
	ETSIDI::play("sonidos/enroque.wav");
	if (color) {
		enroqueCortoBlancas = enroqueLargoBlancas = false;
	}
	else {
		enroqueCortoNegras = enroqueLargoNegras = false;
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
		if (enroqueCortoBlancas == true && enroqueLargoBlancas == true || enroqueCortoNegras == true && enroqueLargoNegras == true)
  {
	bool esEnroque = (abs(pos_y - destino.y) >= 3 &&  // 3 o más casillas
		abs(matriz[pos_x][pos_y]) == REY);

	if (esEnroque) {
		RealizarEnroque(destino.y > pos_y); // true=corto, false=largo
		color = !color;
		posicion_selecc = -1;
		movimientos_posibles.clear();
		return;
	}
  }

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

void Tablero::inicializa(const int& tipojuego)
{
	tipo_juego = tipojuego;

	static GLuint fondoTexture = 0;
	if (fondoTexture == 0) {
		fondoTexture = ETSIDI::getTexture("imagenes/FONDO.png").id;
		glBindTexture(GL_TEXTURE_2D, fondoTexture);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	}

	// Configuración gráfica del tablero (8x10 casillas)
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 10; j++) {
			Casillero[i][j].param_x = { j * 4 };
			Casillero[i][j].param_y = { i * 4 };
			Posic_Casillas[i][j] = { Casillero[i][j].param_x + 1, Casillero[i][j].param_y + 1 }; //para hallar el centro de las casillas
			if ((i + j) & 1) {
				// Color madera oscura para las "casillas negras"
				Casillero[i][j].colorR = 101;
				Casillero[i][j].colorG = 67;
				Casillero[i][j].colorB = 33;
			}
			else {
				// Color crema para las "casillas blancas"
				Casillero[i][j].colorR = 245;
				Casillero[i][j].colorG = 222;
				Casillero[i][j].colorB = 179;
			}
		}
	}

	// Inicialización de piezas según tipo de juego
	if (tipo_juego == 0) { 
		matriz =
		{
			{ TORRE, CABALLO, ARZOBISPO, ALFIL, DAMA, REY, ALFIL, CANCILLER, CABALLO, TORRE },				//Piezas blancas
			{ PEON, PEON, PEON, PEON, PEON , PEON, PEON, PEON, PEON, PEON},									
	
			// Filas vacías al inicio de la partida
			{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},		   
			{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
			{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
			{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},

			{ -PEON, -PEON, -PEON, -PEON, -PEON, -PEON, -PEON, -PEON, -PEON, -PEON },						//Piezas negras
			{ -TORRE, -CABALLO, -ARZOBISPO, -ALFIL, -DAMA, -REY, -ALFIL, -CANCILLER, -CABALLO, -TORRE}		
		};
	}

	// Crear objetos Pieza según la matriz
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			if (matriz[i][j] != 0) {
				Pieza* p = new Pieza(i, j, matriz[i][j]); 
				piezas.push_back(p);
			}
		}
	}

	// Inicialización de las variables
	mov_x_IA = -1, mov_y_IA = -1;
	posicion_selecc = -1;
	pos_x = -1, pos_y = -1;
	pos_x_IA = 0, pos_y_IA = 0;
	color = true;	    // INSTRUCCIÓN PARA QUE LAS BLANCAS EMPIECEN
	jaqblancas = jaqmateblancas =  jaqnegras = jaqmatenegras = tablas = false;

	// Configuración del marcador
	marcador_x = 5.0f;
	marcador_y = 34.0f;
	marcador_ancho = 30.0f;
	marcador_alto = 3.0f;
	marcador_colorR = 50;
	marcador_colorG = 50;
	marcador_colorB = 50;
}




void Tablero::DibujarMarcadorTurno() {

	// Dibujar fondo del marcador
	glDisable(GL_LIGHTING);
	glDisable(GL_TEXTURE_2D);

	// Fondo
	glColor3ub(marcador_colorR, marcador_colorG, marcador_colorB);
	glBegin(GL_QUADS);
	glVertex3f(marcador_x, marcador_y, 0);
	glVertex3f(marcador_x + marcador_ancho, marcador_y, 0);
	glVertex3f(marcador_x + marcador_ancho, marcador_y + marcador_alto, 0);
	glVertex3f(marcador_x, marcador_y + marcador_alto, 0);
	glEnd();


	// Dibujar icono del rey
	glEnable(GL_TEXTURE_2D);

	if (color) { // Turno blancas
		ETSIDI::Sprite rey_w = { "imagenes/rey_w.png" };
		glPushMatrix();
		glTranslatef(marcador_x - 4.0f, marcador_y - 0.8f, 1); // Ajusta posición
		rey_w.setSize(4.0, 4.0);
		rey_w.draw();
		glPopMatrix();
	}
	else {   // Turno negras
		ETSIDI::Sprite rey_b = { "imagenes/rey_b.png" };
		glPushMatrix();
		glTranslatef(marcador_x - 4.0f, marcador_y - 1.1f, 1); // Ajusta posición
		rey_b.setSize(4.5, 4.5);
		rey_b.draw();
		glPopMatrix();
	}


	// Texto
	glDisable(GL_TEXTURE_2D);
	glColor3f(1, 1, 1);
	ETSIDI::setFont("fuentes/Bitwise.ttf", 24);
	ETSIDI::printxy(color ? "TURNO: BLANCAS" : "TURNO: NEGRAS",
		marcador_x + 2, marcador_y + 1);

	glEnable(GL_TEXTURE_2D);
	glEnable(GL_LIGHTING);
}





void Tablero::Auto_Mov() {

	bool verifica_mov = false;
	
	// Buscar pieza negra para mover
		for (int i = 0; i < 8 && !verifica_mov; i++) {
			for (int j = 9; j >= 0 && !verifica_mov; j--) {

				if (matriz[i][j] < 0) {
					pos_x = i;
					pos_y = j;

					// Encontrar la pieza en el vector
					for (int z = 0; z < static_cast<int>(piezas.size()); z++) { 
						if (piezas[z]->Get_Posicion().x == pos_x && piezas[z]->Get_Posicion().y == pos_y) {
							posicion_selecc = z;
							break;
						}
					}

					// Buscar movimiento válido
					for (int l = 0; l < 8 && !verifica_mov; l++) {
						for (int k = 0; k < 10 && !verifica_mov; k++) {

							if (Selec_Mover(l, k, true)) {
								mov_x_IA = l;
								mov_y_IA = k;
								verifica_mov = true;
								
							}
						}

					}

				}
			}
		}
		ETSIDI::play("sonidos/mover.wav");

		// Comer pieza blanca si es necesario
		if (matriz[mov_x_IA][mov_y_IA] > 0) {
			for (int z = 0; z < static_cast<int>(piezas.size()); z++) {
				if (piezas[z]->Get_Posicion().x == mov_x_IA && piezas[z]->Get_Posicion().y == mov_y_IA) {
					ETSIDI::play("sonidos/ComerPieza.wav");
					delete piezas[z];
					if (z < posicion_selecc) posicion_selecc--;
					piezas.erase(piezas.begin() + z);
				}
			}
		}

		// Realizar movimiento
		Coronar(posicion_selecc, pos_x, pos_y, { mov_x_IA, mov_y_IA });
		piezas[posicion_selecc]->Set_Posicion(mov_x_IA, mov_y_IA);

		//Actualización de los valores
		matriz[mov_x_IA][mov_y_IA] = matriz[pos_x][pos_y];
		matriz[pos_x][pos_y] = 0;

		Comprobar_Jaque();		// Verificación de jaque
		color = true;			// Turno de las blancas
		Comprobar_JaqueMate();	// Comprobar si el jugador esta en jaque mate
		posicion_selecc = -1;

}


bool Tablero::Consultar_Turno() {
	return color;
}

void Tablero::setDificultadIA(int dificultad) {
	delete ia_actual;  // Limpiar IA anterior

	switch (dificultad) {
	case 0: ia_actual = new IA_Facil(); break;
	case 1: ia_actual = new IA_Medio(); break;
	case 2: ia_actual = new IA_Dificil(); break;
	default: ia_actual = new IA_Facil();
	}
}

void Tablero::Auto_Mov() {

	if (ia_actual) {
		// Realizar movimiento
		ia_actual->mover(*this);
	}
}

void Tablero::Auto_Mov_Medio() {

	IA_Medio ia;
	ia.mover(*this);
}


void Tablero::Auto_Mov_Dificil() {
	IA_Dificil ia;
	ia.mover(*this);
}


void Tablero::RealizarMovimientoIA(int mov_x, int mov_y, int pos_sel) {

	// Comer cualquier pieza en el destino
	if (matriz[mov_x][mov_y] != 0) {
		for (int z = 0; z < static_cast<int>(piezas.size()); z++) {
			if (piezas[z]->Get_Posicion().x == mov_x &&
				piezas[z]->Get_Posicion().y == mov_y) {
				ETSIDI::play("sonidos/ComerPieza.wav");
				delete piezas[z];
				if (z < pos_sel) pos_sel--;
				piezas.erase(piezas.begin() + z);
				break;
			}
		}
	}

	// Guardar posición original para coronación
	Vector origen = piezas[pos_sel]->Get_Posicion();

	// Mover la pieza
	piezas[pos_sel]->Set_Posicion(mov_x, mov_y);

	// Actualizar matriz
	matriz[mov_x][mov_y] = matriz[origen.x][origen.y];
	matriz[origen.x][origen.y] = 0;

	// Coronar si es necesario
	Coronar(pos_sel, origen.x, origen.y, { mov_x, mov_y });

	Comprobar_Jaque();
	color = true;  // Cambiar turno a blancas
	Comprobar_JaqueMate();
}



bool Tablero::Selec_Mover(int i, int j, bool f) {
	if (pos_x < 0 || pos_y < 0) return false;  // Posición inválida

	bool movimientoValido = false;
	int tipoPieza = abs(matriz[pos_x][pos_y]);

	// Delegar a función específica según tipo de pieza
	switch (tipoPieza) {
	case PEON: movimientoValido = Selec_Peon(i, j); break;
	case REY: movimientoValido = Selec_Rey(i, j); break;
	case DAMA: movimientoValido = Selec_Dama(i, j); break;
	case ALFIL: movimientoValido = Selec_Alfil(i, j); break;
	case CABALLO: movimientoValido = Selec_Caballo(i, j); break;
	case TORRE: movimientoValido = Selec_Torre(i, j); break;
	case ARZOBISPO: movimientoValido = Selec_Arzobispo(i, j); break;
	case CANCILLER: movimientoValido = Selec_Canciller(i, j); break;
	}

	// Verificar si el movimiento deja al rey en jaque
	if (f && movimientoValido) {
		int piezaDestino = matriz[i][j];
		matriz[i][j] = matriz[pos_x][pos_y];
		matriz[pos_x][pos_y] = 0;

		if (Jaque(color)) {  // Si queda en jaque, movimiento inválido
			movimientoValido = false;
		}

		// Revertir movimiento simulado
		matriz[pos_x][pos_y] = matriz[i][j];
		matriz[i][j] = piezaDestino;
	}

	return movimientoValido;
}

//Verifica si el color del rey especificado está en jaque o no
bool Tablero::Jaque(bool col) {
	int rey_i = 0, rey_j = 0;

	// Buscar posición del rey
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 10; j++) {
			if ((col && matriz[i][j] == REY) || (!col && matriz[i][j] == -REY)) {
				rey_i = i; rey_j = j;
				break;
			}
		}
	}

	// Verificar si alguna pieza enemiga puede capturar al rey
	bool turnoOriginal = color;
	color = !col;  // Cambiar temporalmente el turno para verificar desde perspectiva del oponente
	int temp_x = pos_x, temp_y = pos_y;

	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 10; j++) {
			if ((col && matriz[i][j] < 0) || (!col && matriz[i][j] > 0)) {
				pos_x = i; pos_y = j;
				if (Selec_Mover(rey_i, rey_j, false)) {  // Verificar si puede capturar al rey
					pos_x = temp_x; pos_y = temp_y;
					color = turnoOriginal;
					return true;
				}
			}
		}
	}

	// Restaurar valores originales
	pos_x = temp_x; pos_y = temp_y;
	color = turnoOriginal;
	return false;
}


bool Tablero::Selec_Peon(int i, int j) {
	bool sol = false;

	if (color) { //blancas
		if (matriz[i][j] == 0 && j == pos_y && i == (pos_x + 1) ) { sol = true; } //movimiento sin comer
		if (matriz[i][j] != 0 && (j == (pos_y + 1) || j == (pos_y - 1)) && i == (pos_x + 1)) {sol = true;} //movimiento comiendo
	}
	else{ //negras
		if (matriz[i][j] == 0 && j == pos_y && i == (pos_x - 1)) { sol = true; } //movimiento sin comer
		if (matriz[i][j] != 0 && (j == (pos_y + 1) || j == (pos_y - 1)) && i == (pos_x - 1)) { sol = true; }; //movimiento comiendo
	}
	return sol;
}

bool Tablero::Selec_Rey(int i, int j) {
	// Movimiento normal del rey (1 casilla)
if (abs(pos_x - i) <= 1 && abs(pos_y - j) <= 1) {
	return true;
}
// Enroque (detección de movimiento largo)
if (abs(pos_y - j) >= 3 && pos_x == i) {  // 3 o más casillas
	return Selec_Enroque(i, j);
}
return false;
}

bool Tablero::Selec_Alfil(int i, int j) { 
	if (abs(pos_y - j) == abs(pos_x - i)) {
		int valorii = (pos_x - i < 0 ? 1 : -1);
		int valorjj = (pos_y - j < 0 ? 1 : -1);
		int ii = pos_x;
		int jj = pos_y;

		while (ii != i - valorii && jj != j - valorjj) {
			ii += valorii;
			jj += valorjj;
			if (ii < 0 || jj < 0)return false;
			else if (matriz[ii][jj] != 0)return false;
		}
		if (matriz[i][j] == 0) return true;
		if (color && matriz[i][j] != 0) return true;
		else if (!color && matriz[i][j] != 0)return true;
	}
	return false;
}

bool Tablero::Selec_Caballo(int i, int j) {
	bool sol = false;
	if (color) {
		if (((abs(pos_x - i) == 2 && abs(pos_y - j) == 1) || (abs(pos_x - i) == 1) && abs(pos_y - j) == 2)) sol = true;
	}
	else {
		if (((abs(pos_x - i) == 2 && abs(pos_y - j) == 1) || (abs(pos_x - i) == 1) && abs(pos_y - j) == 2)) sol = true;
	}
	return sol;
}

bool Tablero::Selec_Torre(int i, int j) {
	if (pos_y == j) {

		for (int ii = std::min(pos_x, i) + 1; ii < std::max(pos_x, i); ii++) {
			if (matriz[ii][pos_y] != 0) return false;
		}

		if (matriz[i][j] == 0) return true;
		if (color && matriz[i][j] != 0) return true;
		if (!color && matriz[i][j] != 0)return true;
	}
	if (pos_x == i) {

		for (int jj = std::min(pos_y, j) + 1; jj < std::max(pos_y, j); jj++) {
			if (matriz[pos_x][jj] != 0) return false;
		}

		if (matriz[i][j] == 0) return true;
		if (color && matriz[i][j] != 0) return true;
		if (!color && matriz[i][j] != 0) return true;
	}
	return false;
}

bool Tablero::Selec_Dama(int i, int j) {
	if (Selec_Torre(i, j) || Selec_Alfil(i, j))return true;
	return false;
}

bool Tablero::Selec_Arzobispo(int i, int j) {
	if (Selec_Caballo(i, j) || Selec_Alfil(i, j))return true;
	return false;
}

bool Tablero::Selec_Canciller(int i, int j) {
	if (Selec_Torre(i, j) || Selec_Caballo(i, j))return true;
	return false;
}

void Tablero::Coronar(int posicion_selecc, int pos_x, int pos_y, Vector destino) {
	// Coronar peón blanco (llegada a fila 7)
	if (destino.x == 7 && piezas[posicion_selecc]->Get_Valor() == PEON) {
		piezas[posicion_selecc]->Cambiar_Valor(DAMA);
		matriz[pos_x][pos_y] = DAMA;
	}
	// Coronar peón negro (llegada a fila 0)
	else if (destino.x == 0 && piezas[posicion_selecc]->Get_Valor() == -PEON) {
		piezas[posicion_selecc]->Cambiar_Valor(-DAMA);
		matriz[pos_x][pos_y] = -DAMA;
	}
}


//Verifica si el jugador actual está en Jaque Mate o no
void Tablero::Comprobar_JaqueMate() {
	bool esJaqueMate = true;
	bool escapeEncontrado = false;

	// Verificar todas las piezas del jugador en turno
	for (int i = 0; i < 8 && !escapeEncontrado; i++) {
		for (int j = 0; j < 10 && !escapeEncontrado; j++) {
			if ((color && matriz[i][j] > 0) || (!color && matriz[i][j] < 0)) {
				pos_x = i; pos_y = j;


				for (int l = 0; l < 8 && !escapeEncontrado; l++) {
					for (int k = 0; k < 10 && !escapeEncontrado; k++) {
						if (Selec_Mover(l, k, true)) { 
							esJaqueMate = false;
							escapeEncontrado = true;
						}
					}
				}
			}
		}
	}

	// Actualizar estado de jaque mate
	if (esJaqueMate) {
		if (color) {
			jaqmateblancas = true;
		}
		else {
			jaqmatenegras = true;
		}
	}
	else {
		jaqmateblancas = jaqmatenegras = false;
	}

	// Verificar tablas
	if ((jaqmatenegras && !jaqnegras) || (jaqmateblancas && !jaqblancas)) {
		tablas = true;
	}
}


void Tablero::Comprobar_Jaque() {

	if (Jaque(!color)) {
		if (color) {
			jaqnegras = true;
		}
		else {
			jaqblancas = true;
		}
	}
	else {
		if (color)
			jaqnegras = false;
		else
			jaqblancas = false;
	}

}

void Tablero::Borrar() {
	//Eliminar todas las piezas del tablero y reiniciar la matriz de juego
	for (int z = 0; z < static_cast<int>(piezas.size()); z++) {
		delete piezas[z];
	}
	piezas.clear();  // Vaciar el vector

	// Limpiar la matriz
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 10; j++) {
			matriz[i][j] = 0;
		}
	}
}
