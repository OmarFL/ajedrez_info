#pragma once
#include "IA_Movimientos.h"
#include "freeglut.h"
#include "Tablero.h"
#include "mundo.h"
#include <iostream>
#include <chrono>
#include <thread>
#include <vector>
#include <random>
#include <algorithm> 
#include <tuple>
#include <cstdlib> 
#include <ctime>  
#include <set>
/*-------------------------------------------------DIFICULTAD FÁCIL---------------------------------------------------------*/

void IA_Facil::mover(Tablero& tablero) {

    verifica_mov = false;

    auto& matriz = tablero.getMatriz();
    auto& piezas = tablero.getPiezas();

    //tuple: para agrupar en un sólo objeto los valores de movimeinto, en lugar de usar una estructura
    vector<tuple<int, int, int, int, int>> allMoves;  // (pieza_idx, origen_x, origen_y, dest_x, dest_y)

    //recopilar TODOS los movimientos válidos
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 10; j++) {
            if (matriz[i][j] < 0) { //piezas negras (IA)

                //guardar posición actual
                int temp_pos_x = tablero.getPosX();
                int temp_pos_y = tablero.getPosY();

                //establecer posición actual para validación
                tablero.setPosicionSeleccionada(i, j);

                //buscar índice de la pieza
                int piece_index = -1;
                for (int z = 0; z < piezas.size(); z++) {
                    if (piezas[z]->Get_Posicion().x == i &&
                        piezas[z]->Get_Posicion().y == j) {
                        piece_index = z;
                        break;
                    }
                }
                if (piece_index == -1) continue;

                //buscar movimientos válidos
                for (int l = 0; l < 8; l++) {
                    for (int k = 0; k < 10; k++) {
                        if (tablero.Selec_Mover(l, k, true)) {
                            allMoves.push_back(std::make_tuple(piece_index, i, j, l, k));
                        }
                    }
                }

                //restaurar posición original
                tablero.setPosicionSeleccionada(temp_pos_x, temp_pos_y);
            }
        }
    }

    //seleccionar movimiento aleatorio
    if (!allMoves.empty()) {
        int randomIndex = rand() % allMoves.size();
        auto& move = allMoves[randomIndex];

        posicion_selecc = std::get<0>(move);
        int origen_x = std::get<1>(move);
        int origen_y = std::get<2>(move);
        mov_x_IA = std::get<3>(move);
        mov_y_IA = std::get<4>(move);
        verifica_mov = true;

        //establecer posición de origen para el movimiento
        tablero.setPosicionSeleccionada(origen_x, origen_y);

        //reproducir sonido de selección de pieza
        ETSIDI::play("sonidos/mover_bot.wav");   

        tablero.RealizarMovimientoIA(mov_x_IA, mov_y_IA, posicion_selecc);
    }
}



/*-------------------------------------------------DIFICULTAD MEDIA--------------------------------------------------------*/

    //El criterio que seguirá ahora la IA para comer piezas dependerá de una escala de jerarquías
    //La idea es que a mayor valor tenga la pieza, más prioritario será para el bot comerse dicha pieza
    //Comerse una pieza propia será muy negativo para la puntuación considerada, por lo que será la última opción
    //Poner piezas propias en riesgo de ser comidas por el jugador humano también será penalizado


void IA_Medio::mover(Tablero& tablero) {

    verifica_mov = false;

    auto& matriz = tablero.getMatriz();
    auto& piezas = tablero.getPiezas();

    vector<tuple<int, int, int,int, int>> allMoves;  // (pieza_idx, origen_x, origen_y, dest_x, dest_y)
    vector<float> puntuaciones;  // Almacena la puntuación de cada movimiento

    //recopilar TODOS los movimientos válidos
    for (int i = 0; i < 8; i++) {

        for (int j = 0; j < 10; j++) {

            if (matriz[i][j] < 0) { // Piezas negras (IA)
                //guardar posición actual
                int temp_pos_x = tablero.getPosX();
                int temp_pos_y = tablero.getPosY();

                // Establecer posición actual para validación
                tablero.setPosicionSeleccionada(i, j);

                //establecer posición actual para validación
                int indice_pieza = -1;
                for (int z = 0; z < static_cast<int>(piezas.size()); z++) {
                    if (piezas[z]->Get_Posicion().x == i &&
                        piezas[z]->Get_Posicion().y == j) {
                        indice_pieza = z;
                        break;
                    }
                }
                if (indice_pieza == -1) continue;

                //buscar movimientos válidos
                for (int l = 0; l < 8; l++) {
                    for (int k = 0; k < 10; k++) {
                        if (tablero.Selec_Mover(l, k, true)) {
                            allMoves.push_back(std::make_tuple(indice_pieza, i, j, l, k));
                        }
                    }
                }

                //restaurar posición original
                tablero.setPosicionSeleccionada(temp_pos_x, temp_pos_y);
            }
        }
    }

    //Cuando no haya movs, se sale
    if (allMoves.empty()) {
        verifica_mov = false;
        return;
    }

    //criterio de puntuación para cada movimiento:
    puntuaciones.resize(allMoves.size(), 0.0f);

    for (size_t i = 0; i < allMoves.size(); i++) {
        auto& move = allMoves[i];
        int indice_pieza = std::get<0>(move);
        int origen_x = std::get<1>(move);
        int origen_y = std::get<2>(move);
        int dest_x = std::get<3>(move);
        int dest_y = std::get<4>(move);

        float puntuacion = 0.0f;

        //1) puntuación aumenta al comerse una pieza enemiga
        if (matriz[dest_x][dest_y] > 0) { // Pieza blanca (enemiga)
            puntuacion += obtenerValorPieza(matriz[dest_x][dest_y]);
        }

        //2) penalización de puntuación al comerse una pieza propia (x10)
        if (matriz[dest_x][dest_y] < 0) { // Pieza negra (propia)
            puntuacion -= 10 * obtenerValorPieza(abs(matriz[dest_x][dest_y]));
        }

        //3) penalización menor si al mover dejamos la pieza en posición vulnerable
        if (estaBajoAtaque(tablero, dest_x, dest_y, true)) { // true = pieza negra
            int valorPieza = obtenerValorPieza(abs(matriz[origen_x][origen_y]));
            puntuacion -= 0.5 * valorPieza;
        }

        puntuaciones[i] = puntuacion;
    }


    //FASE DE SELECCIÓN: Se escoge el mejor mov, o bien uno aleatorio entre los mejores
    float maxPuntuacion = *std::max_element(puntuaciones.begin(), puntuaciones.end());
    vector<int> mejoresIndices;

    for (size_t i = 0; i < puntuaciones.size(); i++) {
        if (puntuaciones[i] == maxPuntuacion) {
            mejoresIndices.push_back(i);
        }
    }

    int indiceElegido = mejoresIndices[rand() % mejoresIndices.size()];
    auto& mejorMove = allMoves[indiceElegido];

    posicion_selecc = std::get<0>(mejorMove);
    int origen_x = std::get<1>(mejorMove);
    int origen_y = std::get<2>(mejorMove);
    mov_x_IA = std::get<3>(mejorMove);
    mov_y_IA = std::get<4>(mejorMove);
    verifica_mov = true;



    //establecer posición de origen para el movimiento
    tablero.setPosicionSeleccionada(origen_x, origen_y);
    ETSIDI::play("sonidos/mover_bot.wav");

    tablero.RealizarMovimientoIA(mov_x_IA, mov_y_IA, posicion_selecc);
}


int IA_Medio::getMovX() const { return mov_x_IA; }
int IA_Medio::getMovY() const { return mov_y_IA; }
bool IA_Medio::getVerificaMov() const { return verifica_mov; }
int IA_Medio::getPosicionSelecc() const { return posicion_selecc; }


//función para obtener valor de pieza
int IA_Medio::obtenerValorPieza(int tipoPieza) {

    switch (tipoPieza) {

    case 1: return VALOR_PEON;       // PEON
    case 2: return VALOR_CABALLO;    // CABALLO
    case 3: return VALOR_ALFIL;      // ALFIL
    case 4: return VALOR_TORRE;      // TORRE
    case 5: return VALOR_DAMA;       // DAMA
    case 6: return VALOR_REY;        // REY
    case 7: return VALOR_ARZOBISPO;  // ARZOBISPO
    case 8: return VALOR_CANCILLER;  // CANCILLER

    default: return 0;
    }
}



//función para verificar si una posición está bajo ataque
bool IA_Medio::estaBajoAtaque(Tablero& tablero, int x, int y, bool esPiezaNegra) {
    auto& matriz = tablero.getMatriz();
    int temp_pos_x = tablero.getPosX();
    int temp_pos_y = tablero.getPosY();

    //verificar todas las piezas enemigas
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 10; j++) {
            
            //piezas del oponente
            if ((esPiezaNegra && matriz[i][j] > 0) || (!esPiezaNegra && matriz[i][j] < 0)) { 
                tablero.setPosicionSeleccionada(i, j);
                if (tablero.Selec_Mover(x, y, false)) {  //false = no validar jaque
                    tablero.setPosicionSeleccionada(temp_pos_x, temp_pos_y);
                    return true;
                }
            }
        }
    }

    tablero.setPosicionSeleccionada(temp_pos_x, temp_pos_y);
    return false;
}



int IA_Facil::getMovX() const { return mov_x_IA; }
int IA_Facil::getMovY() const { return mov_y_IA; }
bool IA_Facil::getVerificaMov() const { return verifica_mov; }
int IA_Facil::getPosicionSelecc() const { return posicion_selecc; }



/*-------------------------------------------------DIFICULTAD DIFÍCIL--------------------------------------------------------*/


void IA_Dificil::mover(Tablero& tablero) {
    verifica_mov = false;
    auto& matriz = tablero.getMatriz();
    auto& piezas = tablero.getPiezas();
    std::vector<std::tuple<int, int, int, int>> historialMovimientos;

    // 1. Generar todos los movimientos válidos
    vector<tuple<int, int, int, int, int>> allMoves = generarTodosMovimientos(tablero, true);

    if (allMoves.empty()) {
        verifica_mov = false;
        return;
    }

    // 2. Evaluar cada movimiento con criterios más estrictos
    vector<float> puntuaciones;
    for (size_t i = 0; i < allMoves.size(); i++) {
        auto& move = allMoves[i];
        int indice_pieza = std::get<0>(move);
        int origen_x = std::get<1>(move);
        int origen_y = std::get<2>(move);
        int dest_x = std::get<3>(move);
        int dest_y = std::get<4>(move);

        int tipoPieza = abs(matriz[origen_x][origen_y]);
        int valorPieza = obtenerValorPieza(tipoPieza);
        int valorCaptura = (matriz[dest_x][dest_y] > 0) ?
            obtenerValorPieza(matriz[dest_x][dest_y]) : 0;

        float puntuacion = 0.0f;
        bool estaAmenazada = estaBajoAtaque(tablero, dest_x, dest_y, true);

        // A. EVALUACIÓN DE CAPTURAS (con protección de piezas valiosas)
        if (valorCaptura > 0) {
            // Bonus por capturar (mayor para piezas menores)
            float factorCaptura = (valorPieza < VALOR_TORRE) ? 1.8f : 1.2f;
            puntuacion += valorCaptura * factorCaptura;

            // Penalización EXTREMA si pieza valiosa queda expuesta
            if (valorPieza > VALOR_TORRE && estaAmenazada) {
                puntuacion -= valorPieza * 2.0f;  // Penalización doble del valor
            }
        }

        // B. EVALUACIÓN DE RIESGO PARA PIEZAS VALIOSAS
        if (valorPieza > VALOR_CABALLO) {
            // Penalización fuerte por exponer piezas importantes
            if (estaAmenazada) {
                puntuacion -= valorPieza * 1.5f;

                // Penalización adicional si la amenaza viene de pieza menor
                if (valorPieza > VALOR_TORRE) {
                    int valorAmenaza = valorAmenazaMinima(tablero, dest_x, dest_y);
                    if (valorAmenaza < valorPieza) {
                        puntuacion -= (valorPieza - valorAmenaza) * 1.2f;
                    }
                }
            }
        }

        // C. ESTRATEGIA PARA PEONES (avance seguro)
        if (tipoPieza == 1) {
            // Bonus por avance controlado
            int avance = dest_x - origen_x;
            puntuacion += avance * 2;

            // Penalización MUY FUERTE si queda expuesto a captura por peón enemigo
            if (esVulnerableAPeon(tablero, dest_x, dest_y)) {
                puntuacion -= 100;
            }

            // Bonus extra si está protegido por otro peón
            if (estaProtegidoPorPeon(tablero, dest_x, dest_y)) {
                puntuacion += 30;
            }
        }

        // D. ESTRATEGIA DE APERTURA
        if (contadorTurnos < 10) {
            // Bonus por desarrollar piezas menores
            if (origen_x == 0 && (tipoPieza == 2 || tipoPieza == 3)) {
                puntuacion += 40;
            }

            // Penalización por mover dama temprano
            if (tipoPieza == 5) {
                puntuacion -= 80;
            }
        }

        // E. CONTROL POSICIONAL
        // Bonus por control central (reducido para peones)
        if ((dest_x == 3 || dest_x == 4) && (dest_y == 4 || dest_y == 5)) {
            puntuacion += (tipoPieza == PEON) ? 5 : 15;
        }

        // F. EVITAR REPETICIÓN
        for (const auto& mov : historialMovimientos) {
            if (mov == std::make_tuple(origen_x, origen_y, dest_x, dest_y)) {
                puntuacion -= 200;
                break;
            }
        }

        puntuaciones.push_back(puntuacion);
    }

    // 3. Seleccionar el mejor movimiento
    int mejorIndice = 0;
    float mejorPuntuacion = puntuaciones[0];

    for (size_t i = 1; i < puntuaciones.size(); i++) {
        if (puntuaciones[i] > mejorPuntuacion) {
            mejorPuntuacion = puntuaciones[i];
            mejorIndice = i;
        }
    }

    // 4. Realizar movimiento
    auto& mejorMove = allMoves[mejorIndice];
    int indice_pieza = std::get<0>(mejorMove);
    int origen_x = std::get<1>(mejorMove);
    int origen_y = std::get<2>(mejorMove);
    int dest_x = std::get<3>(mejorMove);
    int dest_y = std::get<4>(mejorMove);

    // Actualizar historial
    historialMovimientos.push_back(std::make_tuple(origen_x, origen_y, dest_x, dest_y));
    if (historialMovimientos.size() > 8) {
        historialMovimientos.erase(historialMovimientos.begin());
    }

    contadorTurnos++;

    // Ejecutar movimiento
    tablero.setPosicionSeleccionada(origen_x, origen_y);
    ETSIDI::play("sonidos/mover_bot.wav");
    tablero.RealizarMovimientoIA(dest_x, dest_y, indice_pieza);
    verifica_mov = true;
}


bool IA_Dificil::esVulnerableAPeon(Tablero& tablero, int x, int y) {
    auto& matriz = tablero.getMatriz();

    // Para piezas negras (IA), los peones blancos están abajo (x+1)
    if (x < 7) {
        // Comprobar captura por izquierda
        if (y > 0 && matriz[x + 1][y - 1] == 1) return true;

        // Comprobar captura por derecha
        if (y < 9 && matriz[x + 1][y + 1] == 1) return true;
    }
    return false;
}



bool IA_Dificil::estaProtegidoPorPeon(Tablero& tablero, int x, int y) {
    auto& matriz = tablero.getMatriz();

    // Para piezas negras (IA), los peones protectores están arriba (x-1)
    if (x > 0) {
        // Protección por izquierda
        if (y > 0 && matriz[x - 1][y - 1] == -1) return true;

        // Protección por derecha
        if (y < 9 && matriz[x - 1][y + 1] == -1) return true;
    }
    return false;
}


int IA_Dificil::valorAmenazaMinima(Tablero& tablero, int x, int y) {
    int minValor = 1000;
    auto& matriz = tablero.getMatriz();

    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 10; j++) {
            if (matriz[i][j] > 0) {  // Piezas blancas (enemigas para la IA)
                int tempX = tablero.getPosX();
                int tempY = tablero.getPosY();

                tablero.setPosicionSeleccionada(i, j);
                if (tablero.Selec_Mover(x, y, false)) {
                    int valorAtacante = obtenerValorPieza(matriz[i][j]);
                    if (valorAtacante < minValor) {
                        minValor = valorAtacante;
                    }
                }
                tablero.setPosicionSeleccionada(tempX, tempY);
            }
        }
    }
    return minValor;
}



//función para verificar si una posición está bajo ataque
bool IA_Dificil::estaBajoAtaque(Tablero& tablero, int x, int y, bool esPiezaNegra) {
    auto& matriz = tablero.getMatriz();
    int temp_pos_x = tablero.getPosX();
    int temp_pos_y = tablero.getPosY();

    //verificar todas las piezas enemigas
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 10; j++) {

            //piezas del oponente
            if ((esPiezaNegra && matriz[i][j] > 0) || (!esPiezaNegra && matriz[i][j] < 0)) {
                tablero.setPosicionSeleccionada(i, j);
                if (tablero.Selec_Mover(x, y, false)) {  //false = no validar jaque
                    tablero.setPosicionSeleccionada(temp_pos_x, temp_pos_y);
                    return true;
                }
            }
        }
    }

    tablero.setPosicionSeleccionada(temp_pos_x, temp_pos_y);
    return false;
}



// función para obtener valor de pieza
int IA_Dificil::obtenerValorPieza(int tipoPieza) {

    switch (tipoPieza) {

    case 1: return VALOR_PEON;       // PEON
    case 2: return VALOR_CABALLO;    // CABALLO
    case 3: return VALOR_ALFIL;      // ALFIL
    case 4: return VALOR_TORRE;      // TORRE
    case 5: return VALOR_DAMA;       // DAMA
    case 6: return VALOR_REY;        // REY
    case 7: return VALOR_ARZOBISPO;  // ARZOBISPO
    case 8: return VALOR_CANCILLER;  // CANCILLER

    default: return 0;
    }
}


void IA_Dificil::actualizarFaseJuego(Tablero& tablero) {
    int totalPiezas = 0;
    auto& matriz = tablero.getMatriz();

    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 10; j++) {
            if (matriz[i][j] != 0) totalPiezas++;
        }
    }

    // Menos de 20 piezas = final de juego
    if (totalPiezas < 20) {
        faseActual = FINAL;
    }
    // Entre 20 y 28 piezas = medio juego
    else if (totalPiezas < 28) {
        faseActual = MEDIO_JUEGO;
    }
    // Más de 28 piezas = apertura
    else {
        faseActual = APERTURA;
    }
}

vector<tuple<int, int, int, int, int>> IA_Dificil::generarTodosMovimientos(Tablero& tablero, bool esNegras) {
    auto& matriz = tablero.getMatriz();
    auto& piezas = tablero.getPiezas();
    std::vector<tuple<int, int, int, int, int>> todosMovimientos;

    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 10; j++) {
            // Filtrar piezas del color correcto
            if ((esNegras && matriz[i][j] < 0) || (!esNegras && matriz[i][j] > 0)) {
                int temp_pos_x = tablero.getPosX();
                int temp_pos_y = tablero.getPosY();

                // Establecer posición actual para validación
                tablero.setPosicionSeleccionada(i, j);

                // Buscar índice de la pieza
                int indice_pieza = -1;
                for (int z = 0; z < static_cast<int>(piezas.size()); z++) {
                    if (piezas[z]->Get_Posicion().x == i &&
                        piezas[z]->Get_Posicion().y == j) {
                        indice_pieza = z;
                        break;
                    }
                }
                if (indice_pieza == -1) continue;

                // Buscar movimientos válidos
                for (int x = 0; x < 8; x++) {
                    for (int y = 0; y < 10; y++) {
                        if (tablero.Selec_Mover(x, y, true)) {
                            todosMovimientos.push_back(std::make_tuple(indice_pieza, i, j, x, y));
                        }
                    }
                }

                // Restaurar posición original
                tablero.setPosicionSeleccionada(temp_pos_x, temp_pos_y);
            }
        }
    }

    return todosMovimientos;
}



int IA_Dificil::getMovX() const { return mov_x_IA; }
int IA_Dificil::getMovY() const { return mov_y_IA; }
bool IA_Dificil::getVerificaMov() const { return verifica_mov; }
int IA_Dificil::getPosicionSelecc() const { return posicion_selecc; }



