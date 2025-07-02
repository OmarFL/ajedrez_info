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
                int indice_pieza = -1;
                for (int z = 0; z < piezas.size(); z++) {
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


int IA_Facil::getMovX() const { return mov_x_IA; }
int IA_Facil::getMovY() const { return mov_y_IA; }
bool IA_Facil::getVerificaMov() const { return verifica_mov; }
int IA_Facil::getPosicionSelecc() const { return posicion_selecc; }




/*-------------------------------------------------DIFICULTAD MEDIA--------------------------------------------------------*/

    //El criterio que seguirá ahora la IA para comer piezas dependerá de una escala de jerarquías
    //La idea es que a mayor valor tenga la pieza, más prioritario será para el bot comerse dicha pieza
    //Comerse una pieza propia será muy negativo para la puntuación considerada, por lo que será la última opción
    //Poner piezas propias en riesgo de ser comidas por el jugador humano también será penalizado


void IA_Medio::mover(Tablero& tablero) {

    verifica_mov = false;

    auto& matriz = tablero.getMatriz();
    auto& piezas = tablero.getPiezas();

    vector<tuple<int, int, int,int, int>> allMoves;  //(pieza_idx, origen_x, origen_y, dest_x, dest_y)
    vector<float> puntuaciones;  //Almacena la puntuación de cada movimiento

    //recopilar TODOS los movimientos válidos
    for (int i = 0; i < 8; i++) {

        for (int j = 0; j < 10; j++) {

            if (matriz[i][j] < 0) { // Piezas negras (IA)
                //guardar posición actual
                int temp_pos_x = tablero.getPosX();
                int temp_pos_y = tablero.getPosY();

                //Establecer posición actual para validación
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


/*-------------------------------------------------DIFICULTAD DIFÍCIL--------------------------------------------------------*/

    //Partiendo como base de todo lo que se tenía en el nivel medio de dificultad, se añaden una serie de implementaciones extra:
    
    /*
     - Ahora la IA considera también la posición en el tablero (proriza el control de las piezas que ocupan posiciones centrales), 
     no sólo evalúa la posibilidad de comer.  
     
     - Hace una consideración de todos los posibles movimientos en cada situación, y escoge en todo momento el mejor movimiento,
     eliminando cualquier factor de aleatoriedad cuando exista posibilidad de eliminar una pieza rival de inmediato o en los 
     turnos inmediatamente posteriores (visión a futuro limitada a 1 turno por simplificar)

     - Evalúa cómo de expuestas pueden quedar las piezas después de comer, evitando correr riesgos innecesaios

     - En función de la evolución de la partida, adopta una actitud u otra: En los primeros turnos, prioriza un juego conservador. 
     En "mid game", actúa de forma equilibrada entre movimientos ofensivos y defensivos. En "late game", la IA finalmente se comporta
     de forma más agresiva para forzar victorias y evitar las tablas. 

    */


//ITERACIÓN BASE
/*
void IA_Dificil::mover(Tablero& tablero) {
    verifica_mov = false;
    auto& matriz = tablero.getMatriz();
    auto& piezas = tablero.getPiezas();
    vector<tuple<int, int, int, int>> historialMovimientos;

    // 1. Generar todos los movimientos válidos
    vector<tuple<int, int, int, int, int>> allMoves = generarTodosMovimientos(tablero, true);

    if (allMoves.empty()) {
        verifica_mov = false;
        return;
    }

    // 2. Evaluar cada movimiento con protección reforzada
    vector<float> puntuaciones;
    for (size_t i = 0; i < allMoves.size(); i++) {
        auto& move = allMoves[i];
        int indice_pieza = get<0>(move);
        int origen_x = get<1>(move);
        int origen_y = get<2>(move);
        int dest_x = get<3>(move);
        int dest_y = get<4>(move);

        int tipoPieza = abs(matriz[origen_x][origen_y]);
        int valorPieza = obtenerValorPieza(tipoPieza);
        int valorCaptura = (matriz[dest_x][dest_y] > 0) ?
            obtenerValorPieza(matriz[dest_x][dest_y]) : 0;
        bool esPropia = (matriz[dest_x][dest_y] < 0);
        bool estaAmenazada = estaBajoAtaque(tablero, dest_x, dest_y, true);
        bool capturaAltoValor = (valorCaptura >= VALOR_TORRE);
        bool esPiezaValiosa = (tipoPieza == 5 || tipoPieza == 4 || tipoPieza == 7 || tipoPieza == 8);
        bool esApertura = (contadorTurnos < 10);

        float puntuacion = 0.0f;
        float factorAleatorio = (rand() % 10) * 0.1f;

        // A. PENALIZACIÓN EXTREMA POR COMER PROPIOS
        if (esPropia) {
            puntuacion -= 10000;
        }
        // B. ESTRATEGIA PARA CAPTURAS DE ALTO VALOR
        else if (capturaAltoValor) {
            puntuacion += valorCaptura * 3.0f;

            // Verificar si la pieza quedará vulnerable a captura por piezas de menor valor
            if (estaBajoAtaque(tablero, dest_x, dest_y, true)) {
                int minThreat = valorAmenazaMinima(tablero, dest_x, dest_y);

                // Penalizar fuertemente si la amenaza más pequeña es de bajo valor
                if (minThreat < VALOR_CABALLO) {  // Ej: amenaza de peón
                    puntuacion -= valorPieza * 8.0f;  // Penalización mayor
                }
            }
        }
        // C. PROTECCIÓN REFORZADA PARA PIEZAS VALIOSAS EN APERTURA
        else if (esPiezaValiosa && esApertura) {
            // Penalización base muy fuerte por mover
            puntuacion -= 150;

            // Penalización adicional exponencial si hay amenaza
            if (estaAmenazada) {
                float factorRiesgo = (valorAmenazaMinima(tablero, dest_x, dest_y) < valorPieza) ? 3.5f : 2.0f;
                puntuacion -= valorPieza * factorRiesgo;
            }

            // Bonus mínimo por capturas en apertura
            if (valorCaptura > 0) {
                puntuacion += valorCaptura * 0.3f; // Bonus muy reducido
            }
        }
        // D. ESTRATEGIA PARA PEONES
        else if (tipoPieza == 1) {
            // Bonus agresivo por capturas
            if (valorCaptura > 0) {
                puntuacion += (3.5f + factorAleatorio) * valorCaptura;
            }

            // Avance seguro con variación
            int avance = dest_x - origen_x;
            if (!esVulnerableAPeon(tablero, dest_x, dest_y)) {
                puntuacion += (2.0f + factorAleatorio) * avance;
            }
        }
        // E. ESTRATEGIA PARA CABALLOS Y ALFILES
        else if (tipoPieza == 2 || tipoPieza == 3) {
            // Bonus por desarrollo temprano
            if (esApertura && origen_x == 0) {
                puntuacion += 50 + factorAleatorio * 20;
            }

            // Bonus por control central
            if ((dest_x >= 3 && dest_x <= 4) && (dest_y >= 4 && dest_y <= 5)) {
                puntuacion += 30;
            }
        }

        // F. EVITAR REPETICIÓN
        for (const auto& mov : historialMovimientos) {
            if (mov == make_tuple(origen_x, origen_y, dest_x, dest_y)) {
                puntuacion -= 1000;
                break;
            }
        }


        // Estrategia de final de juego: forzar mate cuando solo queda el rey
        if (oponenteSoloTieneRey(tablero, true)) {
            // Buscar posición del rey enemigo
            int reyX = -1, reyY = -1;
            for (int i = 0; i < 8; i++) {
                for (int j = 0; j < 10; j++) {
                    if (tablero.getMatriz()[i][j] == 6) { // Rey blanco
                        reyX = i;
                        reyY = j;
                    }
                }
            }

            if (reyX != -1) {
                // Gran bonificación por dar jaque mate
                if (tablero.Selec_Mover(reyX, reyY, false)) {
                    // Simular movimiento para ver si es mate
                    int tempValor = tablero.getMatriz()[reyX][reyY];
                    tablero.getMatriz()[reyX][reyY] = tablero.getMatriz()[origen_x][origen_y];
                    tablero.getMatriz()[origen_x][origen_y] = 0;

                    bool esMate = true;
                    // Verificar si el rey tiene escapatoria
                    for (int dx = -1; dx <= 1; dx++) {
                        for (int dy = -1; dy <= 1; dy++) {
                            if (dx == 0 && dy == 0) continue;
                            int nx = reyX + dx;
                            int ny = reyY + dy;
                            if (nx >= 0 && nx < 8 && ny >= 0 && ny < 10) {
                                if (tablero.Selec_Mover(nx, ny, false)) {
                                    esMate = false;
                                }
                            }
                        }
                    }

                    // Restaurar tablero
                    tablero.getMatriz()[origen_x][origen_y] = tablero.getMatriz()[reyX][reyY];
                    tablero.getMatriz()[reyX][reyY] = tempValor;

                    if (esMate) {
                        puntuacion += 5000.0f; // Máxima prioridad a movimientos de mate
                    }
                    else {
                        puntuacion += 100.0f; // Bonificación por jaque
                    }
                }

                // Bonificación por acercar piezas al rey
                float distActual = sqrt(pow(origen_x - reyX, 2) + pow(origen_y - reyY, 2));
                float distNueva = sqrt(pow(dest_x - reyX, 2) + pow(dest_y - reyY, 2));
                if (distNueva < distActual) {
                    puntuacion += 30.0f;
                }

                // Bonificación por controlar casillas alrededor del rey
                for (int dx = -1; dx <= 1; dx++) {
                    for (int dy = -1; dy <= 1; dy++) {
                        if (dx == 0 && dy == 0) continue;
                        if (dx == reyX + dx && dy == reyY + dy) {
                            puntuacion += 25.0f;
                        }
                    }
                }
            }

            // Bonificación por avanzar peones al final de la partida
            if (abs(tablero.getMatriz()[origen_x][origen_y]) == 1) {
                int avance = (tablero.Consultar_Turno() == true) ? (dest_x - origen_x) : (origen_x - dest_x);
                puntuacion += avance * 5.0f;  // Bonificación por avanzar

                // Bonificación extra al final del juego
                if (oponenteSoloTieneRey(tablero, true)) {
                    puntuacion += avance * 8.0f;
                }
            }
        }

        puntuaciones.push_back(puntuacion);
    }

    // 3. Selección con protección de piezas valiosas
    float mejorPuntuacion = -100000;
    vector<int> mejoresIndices;

    // Encontrar la mejor puntuación segura
    for (size_t i = 0; i < puntuaciones.size(); i++) {
        if (puntuaciones[i] > mejorPuntuacion) {
            mejorPuntuacion = puntuaciones[i];
        }
    }

    // Filtrar movimientos peligrosos para piezas valiosas
    for (size_t i = 0; i < puntuaciones.size(); i++) {
        auto& move = allMoves[i];
        int tipoPieza = abs(matriz[get<1>(move)][get<2>(move)]);
        bool esValiosa = (tipoPieza == 5 || tipoPieza == 4 || tipoPieza == 7 || tipoPieza == 8);

        // Solo considerar movimientos seguros para piezas valiosas
        if (esValiosa && contadorTurnos < 10) {
            if (puntuaciones[i] >= mejorPuntuacion - 50.0f) {
                mejoresIndices.push_back(i);
            }
        }
        else if (puntuaciones[i] >= mejorPuntuacion - 20.0f) {
            mejoresIndices.push_back(i);
        }
    }

    // Selección aleatoria entre los mejores movimientos seguros
    int indiceElegido = mejoresIndices[rand() % mejoresIndices.size()];
    auto& mejorMove = allMoves[indiceElegido];

    // 4. Realizar movimiento
    int indice_pieza = get<0>(mejorMove);
    int origen_x = get<1>(mejorMove);
    int origen_y = get<2>(mejorMove);
    int dest_x = get<3>(mejorMove);
    int dest_y = get<4>(mejorMove);

    // Actualizar historial
    historialMovimientos.push_back(make_tuple(origen_x, origen_y, dest_x, dest_y));
    if (historialMovimientos.size() > 10) {
        historialMovimientos.erase(historialMovimientos.begin());
    }

    contadorTurnos++;

    // Ejecutar movimiento
    tablero.setPosicionSeleccionada(origen_x, origen_y);
    ETSIDI::play("sonidos/mover_bot.wav");
    tablero.RealizarMovimientoIA(dest_x, dest_y, indice_pieza);
    verifica_mov = true;
}
*/


//ITERACIÓN DEFINITIVA

void IA_Dificil::mover(Tablero& tablero) {
    verifica_mov = false;
    auto& matriz = tablero.getMatriz();
    auto& piezas = tablero.getPiezas();
    std::vector< std::tuple<int, int, int, int>> historialMovimientos;  //(pieza_idx, origen_x, origen_y, dest_x, dest_y)

    //Se generan primero todos los movimientos válidos
    std::vector< std::tuple<int, int, int, int, int>> allMoves = generarTodosMovimientos(tablero, true);

    if (allMoves.empty()) {
        verifica_mov = false;
        return;
    }

    //1) Evaluar cada movimiento
    std::vector<float> puntuaciones;
    std::vector<bool> esCaptura; //identificar movimientos de captura

    for (size_t i = 0; i < allMoves.size(); i++) {
        auto& move = allMoves[i];
        int indice_pieza = get<0>(move);
        int origen_x = get<1>(move);
        int origen_y = get<2>(move);
        int dest_x = get<3>(move);
        int dest_y = get<4>(move);

        int tipoPieza = abs(matriz[origen_x][origen_y]);
        int valorPieza = obtenerValorPieza(tipoPieza);
        int valorCaptura = (matriz[dest_x][dest_y] > 0) ?
            obtenerValorPieza(matriz[dest_x][dest_y]) : 0;
        bool movimientoEsCaptura = (matriz[dest_x][dest_y] > 0); //captura pieza enemiga (no tocar)
        bool esPropia = (matriz[dest_x][dest_y] < 0);
        bool estaAmenazada = estaBajoAtaque(tablero, dest_x, dest_y, true);
        bool capturaAltoValor = (valorCaptura >= VALOR_TORRE);
        bool esPiezaValiosa = (tipoPieza == 5 || tipoPieza == 4 || tipoPieza == 7 || tipoPieza == 8);
        bool esApertura = (contadorTurnos < 10);

        float puntuacion = 0.0f;
        float factorAleatorio = (rand() % 10) * 0.1f; //aleatoriedad para movimientos que no sean de captura

        //CRITERIOS DE PUNTUACIÓN
        
        // A. PENALIZACIÓN EXTREMA POR COMER PROPIOS
        if (esPropia) {
            puntuacion -= 10000;
        }

        // B. ESTRATEGIA PARA CAPTURAS
        else if (movimientoEsCaptura) {
            puntuacion += valorCaptura * 4.0f;

            //comprobar vulnerabilidad tras capturar
            if (estaBajoAtaque(tablero, dest_x, dest_y, true)) {
                int minThreat = valorAmenazaMinima(tablero, dest_x, dest_y);
                if (minThreat < VALOR_CABALLO) {
                    puntuacion -= valorPieza * 8.0f;
                }
            }
        }

        // C. ESTRATEGIA PARA MOVIMIENTOS POSICIONALES (CON ALEATORIEDAD)
        else {
            //para proteger piezas en la apertura del juego
            if (esPiezaValiosa && esApertura) {
                puntuacion -= 150;
                if (estaAmenazada) {
                    float factorRiesgo = (valorAmenazaMinima(tablero, dest_x, dest_y) < valorPieza) ? 3.5f : 2.0f;
                    puntuacion -= valorPieza * factorRiesgo;
                }
            }
            // ESTRATEGIA PARA PEONES
            else if (tipoPieza == 1) {
                //avance seguro con variación
                int avance = dest_x - origen_x;
                if (!esVulnerableAPeon(tablero, dest_x, dest_y)) {
                    puntuacion += (2.0f + factorAleatorio) * avance;
                }
            }
            // ESTRATEGIA PARA CABALLOS Y ALFILES
            else if (tipoPieza == 2 || tipoPieza == 3) {
                //bonus por moverlos al principio (early game)
                if (esApertura && origen_x == 0) {
                    puntuacion += 50 + factorAleatorio * 20;
                }
                //bonus por mantener el centro
                if ((dest_x >= 3 && dest_x <= 4) && (dest_y >= 4 && dest_y <= 5)) {
                    puntuacion += 30;
                }
            }
        }

        // D. CONSIDERACIONES GENERALES PARA TODOS LOS MOVIMIENTOS
        //Evita repetición
        for (const auto& mov : historialMovimientos) {
            if (mov == std::make_tuple(origen_x, origen_y, dest_x, dest_y)) {
                puntuacion -= 1000;
                break;
            }
        }

        // Estrategia de final de juego: forzar mate cuando solo queda el rey
        if (oponenteSoloTieneRey(tablero, true)) {
            //Busca posición del rey enemigo
            int reyX = -1, reyY = -1;
            for (int i = 0; i < 8; i++) {
                for (int j = 0; j < 10; j++) {
                    if (tablero.getMatriz()[i][j] == 6) { // Rey blanco
                        reyX = i;
                        reyY = j;
                    }
                }
            }

            if (reyX != -1) {
                //Bonificación por jaque mate
                if (tablero.Selec_Mover(reyX, reyY, false)) {
                    //se simula primero el movimiento para ver si es mate
                    int tempValor = tablero.getMatriz()[reyX][reyY];
                    tablero.getMatriz()[reyX][reyY] = tablero.getMatriz()[origen_x][origen_y];
                    tablero.getMatriz()[origen_x][origen_y] = 0;

                    bool esMate = true;
                    //se verifica si el rey tiene escapatoria
                    for (int dx = -1; dx <= 1; dx++) {
                        for (int dy = -1; dy <= 1; dy++) {
                            if (dx == 0 && dy == 0) continue;
                            int nx = reyX + dx;
                            int ny = reyY + dy;
                            if (nx >= 0 && nx < 8 && ny >= 0 && ny < 10) {
                                if (tablero.Selec_Mover(nx, ny, false)) {
                                    esMate = false;
                                }
                            }
                        }
                    }

                    // Restaurar tablero
                    tablero.getMatriz()[origen_x][origen_y] = tablero.getMatriz()[reyX][reyY];
                    tablero.getMatriz()[reyX][reyY] = tempValor;

                    if (esMate) {
                        puntuacion += 5000.0f; //Siempre prioridad a movimientos de jaque mate
                    }
                    else {
                        puntuacion += 100.0f; //si hay jaque
                    }
                }

                //Bonificación por acercar piezas al rey
                float distActual = sqrt(pow(origen_x - reyX, 2) + pow(origen_y - reyY, 2));
                float distNueva = sqrt(pow(dest_x - reyX, 2) + pow(dest_y - reyY, 2));
                if (distNueva < distActual) {
                    puntuacion += 30.0f;
                }

                //Bonificación por controlar casillas alrededor del rey
                for (int dx = -1; dx <= 1; dx++) {
                    for (int dy = -1; dy <= 1; dy++) {
                        if (dx == 0 && dy == 0) continue;
                        if (dx == reyX + dx && dy == reyY + dy) {
                            puntuacion += 25.0f;
                        }
                    }
                }
            }

            //Bonificación por avanzar peones al final de la partida
            if (abs(tablero.getMatriz()[origen_x][origen_y]) == 1) {
                int avance = (tablero.Consultar_Turno() == true) ? (dest_x - origen_x) : (origen_x - dest_x);
                puntuacion += avance * 5.0f;  // Bonificación por avanzar

                // Bonificación extra al final del juego
                if (oponenteSoloTieneRey(tablero, true)) {
                    puntuacion += avance * 8.0f;
                }
            }
        }
        puntuaciones.push_back(puntuacion);
        esCaptura.push_back(movimientoEsCaptura);
    }

    //E. SEPARACIÓN ENTRE MOVIMEINTOS DE CAPTURA Y NO CAPTURA
    std::vector<int> indicesCaptura;
    std::vector<float> puntuacionesCaptura;

    std::vector<int> indicesNoCaptura;
    std::vector<float> puntuacionesNoCaptura;

    for (size_t i = 0; i < allMoves.size(); i++) {
        if (esCaptura[i]) {
            indicesCaptura.push_back(i);
            puntuacionesCaptura.push_back(puntuaciones[i]);
        }
        else {
            indicesNoCaptura.push_back(i);
            puntuacionesNoCaptura.push_back(puntuaciones[i]);
        }
    }

    int indiceElegido = -1;

    //F. CRITERIO DE SELECCIÓN DE MOVIMIENTOS
    if (!indicesCaptura.empty()) {
        //Seleccionar la mejor captura een función de la puntuación
        float mejorPuntuacionCaptura = -100000;
        for (size_t i = 0; i < indicesCaptura.size(); i++) {
            if (puntuacionesCaptura[i] > mejorPuntuacionCaptura) {
                mejorPuntuacionCaptura = puntuacionesCaptura[i];
                indiceElegido = indicesCaptura[i];
            }
        }
    }
    //Aleatoriedad para movimientos que no impliquen comer piezas
    else if (!indicesNoCaptura.empty()) {
        float mejorPuntuacionNoCaptura = *std::max_element(
            puntuacionesNoCaptura.begin(), puntuacionesNoCaptura.end());

        std::vector<int> mejoresIndices;
        for (size_t i = 0; i < indicesNoCaptura.size(); i++) {
            if (puntuacionesNoCaptura[i] >= mejorPuntuacionNoCaptura - 20.0f) {
                mejoresIndices.push_back(indicesNoCaptura[i]);
            }
        }

        if (!mejoresIndices.empty()) {
            indiceElegido = mejoresIndices[rand() % mejoresIndices.size()];
        }
    }

    //si no se seleccionó ningún movimiento
    if (indiceElegido == -1) {
        indiceElegido = 0; // se selecciona el primer movimiento (como último recurso)
    }

    auto& mejorMove = allMoves[indiceElegido];

    //Finalmente se realiza el movimiento
    int indice_pieza = std::get<0>(mejorMove);
    int origen_x = std::get<1>(mejorMove);
    int origen_y = std::get<2>(mejorMove);
    int dest_x = std::get<3>(mejorMove);
    int dest_y = std::get<4>(mejorMove);

    //Actualizar historial
    historialMovimientos.push_back(std::make_tuple(origen_x, origen_y, dest_x, dest_y));
    if (historialMovimientos.size() > 10) {
        historialMovimientos.erase(historialMovimientos.begin());
    }

    contadorTurnos++;

    //Ejecutar movimiento
    tablero.setPosicionSeleccionada(origen_x, origen_y);
    ETSIDI::play("sonidos/mover_bot.wav");
    tablero.RealizarMovimientoIA(dest_x, dest_y, indice_pieza);
    verifica_mov = true;
}




float IA_Dificil::calcularRiesgoCaptura(Tablero& tablero, int ox, int oy, int dx, int dy) {
    auto& matriz = tablero.getMatriz();
    float riesgo = 0.0f;
    int tipoPiezaAtacante = abs(matriz[ox][oy]);
    int valorAtacante = obtenerValorPieza(tipoPiezaAtacante);

    //1. Verificar si la posición destino está amenazada
    if (!estaBajoAtaque(tablero, dx, dy, true)) {
        return 0.0f; //No hay riesgo si no está amenazada
    }

    //2. Encontrar la amenaza de menor valor
    int minValorAmenaza = 10000;
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 10; j++) {
            if (matriz[i][j] > 0) { //piezas blancas
                int tempX = tablero.getPosX();
                int tempY = tablero.getPosY();
                tablero.setPosicionSeleccionada(i, j);

                if (tablero.Selec_Mover(dx, dy, false)) {
                    int valorAmenaza = obtenerValorPieza(matriz[i][j]);
                    if (valorAmenaza < minValorAmenaza) {
                        minValorAmenaza = valorAmenaza;
                    }
                }
                tablero.setPosicionSeleccionada(tempX, tempY);
            }
        }
    }

    //3. Calcular relación de valor
    if (minValorAmenaza == 10000) return 0.0f; //no hay amenazas

    //4. Penalización basada en la relación de valores
    float factorRiesgo = 1.0f;

    //CASO A: Riesgo alto (capturamos pieza de bajo valor y exponemos pieza valiosa)
    if (matriz[dx][dy] > 0) {
        int valorCaptura = obtenerValorPieza(matriz[dx][dy]);
        if (valorCaptura < valorAtacante && minValorAmenaza <= valorAtacante) {
            factorRiesgo = 3.0f; //Penalización fuerte
        }
    }

    //CASO B: Riesgo extremo (intercambio desfavorable)
    if (minValorAmenaza < valorAtacante) {
        factorRiesgo = 5.0f; //Penalización muy fuerte
    }

    //Cálculo final de riesgo
    return valorAtacante * factorRiesgo;
}




bool IA_Dificil::esVulnerableAPeon(Tablero& tablero, int x, int y) {
    auto& matriz = tablero.getMatriz();

    //Para piezas negras (IA), los peones blancos están abajo (x+1)
    if (x < 7) {
        //Comprobar captura por izquierda
        if (y > 0 && matriz[x + 1][y - 1] == 1) return true;

        //Comprobar captura por derecha
        if (y < 9 && matriz[x + 1][y + 1] == 1) return true;
    }
    return false;
}



bool IA_Dificil::estaProtegidoPorPeon(Tablero& tablero, int x, int y) {
    auto& matriz = tablero.getMatriz();

    //Para piezas negras (IA), los peones protectores están arriba (x-1)
    if (x > 0) {
        //Protección por izquierda
        if (y > 0 && matriz[x - 1][y - 1] == -1) return true;

        //Protección por derecha
        if (y < 9 && matriz[x - 1][y + 1] == -1) return true;
    }
    return false;
}


int IA_Dificil::valorAmenazaMinima(Tablero& tablero, int x, int y) {
    int minValor = 1000;
    auto& matriz = tablero.getMatriz();

    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 10; j++) {
            if (matriz[i][j] > 0) {  //Piezas blancas (enemigas)
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

    // Valor especial para peones (amenaza más peligrosa)
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 10; j++) {
            if (matriz[i][j] == 1) {  //Peón blanco
                if ((abs(i - x) == 1 && abs(j - y) == 1)) {
                    if (VALOR_PEON < minValor) {
                        minValor = VALOR_PEON;
                    }
                }
            }
        }
    }

    return minValor;
}


void IA_Dificil::actualizarFaseJuego(Tablero& tablero) {
    int totalPiezas = 0;
    int piezasBlancas = 0;
    auto& matriz = tablero.getMatriz();

    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 10; j++) {
            if (matriz[i][j] != 0) {
                totalPiezas++;
                if (matriz[i][j] > 0) piezasBlancas++;
            }
        }
    }

    //detectar si el oponente solo tiene el rey
    bool oponenteSoloRey = (piezasBlancas == 1);

    //definir fases del juego
    if (totalPiezas < 10 || oponenteSoloRey) {
        faseActual = FINAL;
    }
    else if (totalPiezas < 20) {
        faseActual = MEDIO_JUEGO;
    }
    else {
        faseActual = APERTURA;
    }
}


float IA_Dificil::evaluarApertura(Tablero& tablero, int origen_x, int origen_y, int dest_x, int dest_y) {
    float puntuacion = 0.0f;
    int tipoPieza = abs(tablero.getMatriz()[origen_x][origen_y]);

    //1. Desarrollo muy conservador de piezas valiosas
    if (tipoPieza == VALOR_CABALLO || tipoPieza == VALOR_ALFIL ||
        tipoPieza == VALOR_ARZOBISPO || tipoPieza == VALOR_CANCILLER) {

        if (origen_x == 0 && dest_x > 1) {
            //Bonus reducido para piezas menores
            puntuacion += 8;

            //Penalización severa por avanzar demasiado
            if (dest_x > 3 && contadorTurnos < 6) {
                puntuacion -= 30;
            }

            //Penalización adicional si la casilla destino está atacada
            if (estaBajoAtaque(tablero, dest_x, dest_y, true)) {
                puntuacion -= 20;
            }
        }
    }

    //2. Control del centro con peones
    if (abs(tablero.getMatriz()[origen_x][origen_y]) == 1) { //Peón
        if (dest_y >= 4 && dest_y <= 5 && dest_x == 3) {
            puntuacion += 15;
        }
    }

    //3. Evitar exponer piezas valiosas
    if (estaBajoAtaque(tablero, dest_x, dest_y, true)) {
        int valorPieza = obtenerValorPieza(abs(tablero.getMatriz()[origen_x][origen_y]));
        puntuacion -= valorPieza * 0.7;
    }

    return puntuacion;
}

float IA_Dificil::evaluarMedioJuego(Tablero& tablero, int origen_x, int origen_y, int dest_x, int dest_y) {
    float puntuacion = 0.0f;

    //1. Ataque coordinado
    puntuacion += evaluarAtaqueAlRey(tablero, dest_x, dest_y);

    //2. Movilidad de piezas
    int movilidad = 0;
    int temp_pos_x = tablero.getPosX();
    int temp_pos_y = tablero.getPosY();

    tablero.setPosicionSeleccionada(dest_x, dest_y);
    for (int x = 0; x < 8; x++) {
        for (int y = 0; y < 10; y++) {
            if (tablero.Selec_Mover(x, y, true)) {
                movilidad++;
            }
        }
    }
    tablero.setPosicionSeleccionada(temp_pos_x, temp_pos_y);

    puntuacion += movilidad * 0.5;

    //3. Control de columnas abiertas para torres
    if (abs(tablero.getMatriz()[origen_x][origen_y]) == 4) {    //Torre
        bool columnaAbierta = true;
        for (int i = 0; i < 8; i++) {
            if (tablero.getMatriz()[i][dest_y] == 1 ||   //peón blanco
                tablero.getMatriz()[i][dest_y] == -1) {  //peón negro
                columnaAbierta = false;
                break;
            }

        }
        if (columnaAbierta) puntuacion += 20;
    }

    return puntuacion;
}

float IA_Dificil::evaluarFinal(Tablero& tablero, int origen_x, int origen_y, int dest_x, int dest_y) {
    float puntuacion = 0.0f;

    //1. Activar rey en el final
    if (abs(tablero.getMatriz()[origen_x][origen_y]) == 6) {

        int centroX = 3.5;
        int centroY = 4.5;
        float distanciaCentro = sqrt(pow(dest_x - centroX, 2) + pow(dest_y - centroY, 2));
        puntuacion += (10 - distanciaCentro) * 2;
    }

    //2. Avanzar peones pasados
    if (abs(tablero.getMatriz()[origen_x][origen_y]) == 1) {    //peón
        int avance = (tablero.Consultar_Turno() == true) ? dest_x : (7 - dest_x);
        puntuacion += avance * 5;
    }

    return puntuacion;
}

float IA_Dificil::evaluarAtaqueAlRey(Tablero& tablero, int dest_x, int dest_y) {
    float puntuacion = 0.0f;

    //Encontrar posición del rey enemigo
    int reyX = -1, reyY = -1;
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 10; j++) {
            if (tablero.getMatriz()[i][j] == 6) { //Rey blanco
                reyX = i;
                reyY = j;
                break;
            }
        }
    }

    if (reyX != -1) {
        //Bonus por acercarse al rey enemigo
        float distancia = sqrt(pow(dest_x - reyX, 2) + pow(dest_y - reyY, 2));
        puntuacion += (10 - distancia) * 0.5;

        //Bonus por atacar casillas alrededor del rey
        for (int dx = -1; dx <= 1; dx++) {
            for (int dy = -1; dy <= 1; dy++) {
                if (dx == 0 && dy == 0) continue;
                if (dest_x == reyX + dx && dest_y == reyY + dy) {
                    puntuacion += 15;
                }
            }
        }
    }

    return puntuacion;
}


float IA_Dificil::calcularRiesgo(Tablero& tablero, int origen_x, int origen_y, int dest_x, int dest_y) {
    float riesgo = 0.0f;
    int valorPieza = obtenerValorPieza(abs(tablero.getMatriz()[origen_x][origen_y]));

    //1. Riesgo por estar bajo ataque
    if (estaBajoAtaque(tablero, dest_x, dest_y, true)) {
        riesgo += valorPieza * 0.8f;
    }

    //2. Riesgo por capturas en cadena
    if (tablero.getMatriz()[dest_x][dest_y] > 0) {
        int valorCaptura = obtenerValorPieza(tablero.getMatriz()[dest_x][dest_y]);

        //Calcular posibles contra-capturas
        if (estaBajoAtaque(tablero, dest_x, dest_y, true)) {
            //Encontrar el atacante de menor valor
            int minValorAtacante = 1000;
            for (int i = 0; i < 8; i++) {
                for (int j = 0; j < 10; j++) {
                    if (tablero.getMatriz()[i][j] > 0) {
                        int tempX = tablero.getPosX();
                        int tempY = tablero.getPosY();
                        tablero.setPosicionSeleccionada(i, j);
                        if (tablero.Selec_Mover(dest_x, dest_y, false)) {
                            int valorAtacante = obtenerValorPieza(tablero.getMatriz()[i][j]);
                            if (valorAtacante < minValorAtacante) {
                                minValorAtacante = valorAtacante;
                            }
                        }
                        tablero.setPosicionSeleccionada(tempX, tempY);
                    }
                }
            }

            //Calcular riesgo de intercambio
            if (minValorAtacante < valorPieza) {
                riesgo += (valorPieza - minValorAtacante) * 1.2f;
            }
        }
    }

    return riesgo;
}


std::vector<tuple<int, int, int, int, int>> IA_Dificil::generarTodosMovimientos(Tablero& tablero, bool esNegras) {
    auto& matriz = tablero.getMatriz();
    auto& piezas = tablero.getPiezas();
    std::vector<tuple<int, int, int, int, int>> todosMovimientos;

    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 10; j++) {
            //Filtrar piezas del color correcto
            if ((esNegras && matriz[i][j] < 0) || (!esNegras && matriz[i][j] > 0)) {
                int temp_pos_x = tablero.getPosX();
                int temp_pos_y = tablero.getPosY();

                //Establecer posición actual para validación
                tablero.setPosicionSeleccionada(i, j);

                //Buscar índice de la pieza
                int indice_pieza = -1;
                for (int z = 0; z < static_cast<int>(piezas.size()); z++) {
                    if (piezas[z]->Get_Posicion().x == i &&
                        piezas[z]->Get_Posicion().y == j) {
                        indice_pieza = z;
                        break;
                    }
                }
                if (indice_pieza == -1) continue;

                //Buscar movimientos válidos
                for (int x = 0; x < 8; x++) {
                    for (int y = 0; y < 10; y++) {
                        if (tablero.Selec_Mover(x, y, true)) {
                            todosMovimientos.push_back(make_tuple(indice_pieza, i, j, x, y));
                        }
                    }
                }

                //Restaurar posición original
                tablero.setPosicionSeleccionada(temp_pos_x, temp_pos_y);
            }
        }
    }

    return todosMovimientos;
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


bool IA_Dificil::oponenteSoloTieneRey(Tablero& tablero, bool esNegras) {
    auto& matriz = tablero.getMatriz();
    int piezasOponente = 0;

    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 10; j++) {
            if ((esNegras && matriz[i][j] > 0) || (!esNegras && matriz[i][j] < 0)) {
                int tipoPieza = abs(matriz[i][j]);
                if (tipoPieza != 6) { //Si no es el rey
                    piezasOponente++;
                }
            }
        }
    }
    return (piezasOponente == 0); //Solo queda el rey
}



//función para obtener valor de pieza
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

int IA_Dificil::getMovX() const { return mov_x_IA; }
int IA_Dificil::getMovY() const { return mov_y_IA; }
bool IA_Dificil::getVerificaMov() const { return verifica_mov; }
int IA_Dificil::getPosicionSelecc() const { return posicion_selecc; }
