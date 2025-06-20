#include "Mundo.h"
#include <iostream>

using namespace std;

void Mundo::dibuja()
{
	// Delegamos el dibujado al tablero que contiene las piezas
	tablero.dibuja();

}

void Mundo::inicializa(int tipo_juego, const int& num_rival)
{
	tablero.inicializa(tipo_juego);  // Prepara el tablero según el modo de juego
	tablero.Set_Oponente(num_rival); // Establece el tipo de oponente
}
void Mundo::Boton_Raton(int num_rival, int x, int y, int boton, bool abajo, bool espacio, bool ref_tecla) 
{

    num_rival = tablero.Get_Oponente(); // Actualiza el tipo de oponente

    if (abajo) { // Solo procesar cuando se presiona el botón

        // Configuración para conversión de coordenadas de pantalla a mundo 3D
        GLint viewport[4];
        GLdouble modelview[16], projection[16];
        GLfloat winX, winY, winZ;
        GLdouble posX, posY, posZ;

        // Obtenemos matrices actuales de OpenGL
        glGetDoublev(GL_MODELVIEW_MATRIX, modelview);
        glGetDoublev(GL_PROJECTION_MATRIX, projection);
        glGetIntegerv(GL_VIEWPORT, viewport);

        // Convertimos coordenadas de pantalla a ventana
        winX = (float)x;
        winY = (float)viewport[3] - (float)y; // Invertir coordenada Y

        // Obtenemos profundidad en el pixel clickeado
        glReadPixels(x, int(winY), 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &winZ);

        // Convertimos a coordenadas del mundo 3D
        gluUnProject(winX, winY, winZ, modelview, projection, viewport, &posX, &posY, &posZ);

        // Verificamos si el clic fue dentro del tablero o es turno de la IA
        if ((posY >= -300 && posY <= 144 && posX >= -300 && posX <= 144) ||
            ((!tablero.Consultar_Turno()) && num_rival == 1)) {

            // Modo 1vs1 (humano vs humano)
            if (num_rival == 0) {
                if (boton == GLUT_LEFT_BUTTON) {
                    // Selección de pieza con clic izquierdo
                    Casilla_ini.x = (int)((posY / casillas_ancho));
                    Casilla_ini.y = (int)((posX / casillas_ancho) + 2);
                    tablero.Seleccionar_Pieza_1VS1(Casilla_ini);
                }

                if (boton == GLUT_RIGHT_BUTTON) {
                    // Movimiento de pieza con clic derecho
                    Casilla_fin.x = (int)(posY / casillas_ancho);
                    Casilla_fin.y = (int)((posX / casillas_ancho) + 2);
                    tablero.Mover_Pieza_1VS1(Casilla_fin);
                }
            }

            // Modo contra IA
            if (num_rival == 1) {
                // Solo procesar si es turno del jugador humano
                if (tablero.Consultar_Turno() == true) {
                    if (boton == GLUT_LEFT_BUTTON) {
                        // Selección de pieza
                        Casilla_ini.x = (int)(posY / casillas_ancho);
                        Casilla_ini.y = (int)((posX / casillas_ancho) + 2);
                        tablero.Seleccionar_Pieza_1VS1(Casilla_ini);
                    }

                    if (boton == GLUT_RIGHT_BUTTON) {
                        // Movimiento de pieza
                        Casilla_fin.x = (int)(posY / casillas_ancho);
                        Casilla_fin.y = (int)((posX / casillas_ancho) + 2);
                        tablero.Mover_Pieza_1VS1(Casilla_fin);
                    }
                }
            }
        }
    }

    // Si se soltó el botón y es turno de la IA, hacer movimiento automático
    if (!abajo && num_rival == 1 && !tablero.Consultar_Turno()) {
        std::this_thread::sleep_for(std::chrono::seconds(2)); // Pequeña pausa
        tablero.Auto_Mov(); // La IA realiza su movimiento
    }
}

