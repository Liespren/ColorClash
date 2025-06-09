#include "IA.h"
#include <algorithm>

Estado::Estado(int original[NUM_FILAS][NUM_COLUMNAS], int turno_actual) {
    jugador_actual = turno_actual;
    for (int i = 0; i < NUM_FILAS; ++i) {
        for (int j = 0; j < NUM_COLUMNAS; ++j) {
            tablero[i][j] = original[i][j];
        }
    }
}

IA::IA(int profundidad_maxima) {
    profundidad = profundidad_maxima;
}

Movimiento IA::obtener_mejor_movimiento(int tablero[NUM_FILAS][NUM_COLUMNAS], int jugador) {
    Estado estado_inicial(tablero, jugador);
    Movimiento mejor_movimiento = {-1, -1};
    int mejor_valor = numeric_limits<int>::min();

    for (Movimiento mov : generar_movimientos_validos(estado_inicial)) {
        Estado nuevo_estado = aplicar_movimiento(estado_inicial, mov);
        int valor = minimax(nuevo_estado, profundidad - 1, numeric_limits<int>::min(), numeric_limits<int>::max(), false);
        if (valor > mejor_valor) {
            mejor_valor = valor;
            mejor_movimiento = mov;
        }
    }
    return mejor_movimiento;
}

int IA::minimax(Estado estado, int profundidad_actual, int alpha, int beta, bool es_maximizador) {
    if (profundidad_actual == 0 || generar_movimientos_validos(estado).empty()) {
        return evaluar(estado);
    }

    if (es_maximizador) {
        int max_eval = numeric_limits<int>::min();
        for (Movimiento mov : generar_movimientos_validos(estado)) {
            Estado nuevo_estado = aplicar_movimiento(estado, mov);
            int eval = minimax(nuevo_estado, profundidad_actual - 1, alpha, beta, false);
            max_eval = max(max_eval, eval);
            alpha = max(alpha, eval);
            if (beta <= alpha) break; // poda beta
        }
        return max_eval;
    } else {
        int min_eval = numeric_limits<int>::max();
        for (Movimiento mov : generar_movimientos_validos(estado)) {
            Estado nuevo_estado = aplicar_movimiento(estado, mov);
            int eval = minimax(nuevo_estado, profundidad_actual - 1, alpha, beta, true);
            min_eval = min(min_eval, eval);
            beta = min(beta, eval);
            if (beta <= alpha) break; // poda alfa
        }
        return min_eval;
    }
}

vector<Movimiento> IA::generar_movimientos_validos(const Estado& estado) {
    vector<Movimiento> movimientos;
    bool visitado[NUM_FILAS][NUM_COLUMNAS] = {false};

    for (int i = 0; i < NUM_FILAS; ++i) {
        for (int j = 0; j < NUM_COLUMNAS; ++j) {
            if (estado.tablero[i][j] == estado.jugador_actual) {
                // Revisar vecinos arriba, abajo, izquierda, derecha
                const int dirs[4][2] = {{-1,0},{1,0},{0,-1},{0,1}};
                for (auto& d : dirs) {
                    int ni = i + d[0];
                    int nj = j + d[1];
                    if (ni >= 0 && ni < NUM_FILAS && nj >= 0 && nj < NUM_COLUMNAS) {
                        if (estado.tablero[ni][nj] == 0 && !visitado[ni][nj]) {
                            movimientos.push_back({ni, nj});
                            visitado[ni][nj] = true;
                        }
                    }
                }
            }
        }
    }
    return movimientos;
}

Estado IA::aplicar_movimiento(const Estado& estado, const Movimiento& mov) {
    Estado nuevo_estado = estado;
    nuevo_estado.tablero[mov.fila][mov.columna] = estado.jugador_actual;
    nuevo_estado.jugador_actual = 3 - estado.jugador_actual; // alterna entre 1 y 2
    return nuevo_estado;
}

int IA::evaluar(const Estado& estado) {
    int puntaje_jugador = 0;
    int puntaje_oponente = 0;

    for (int i = 0; i < NUM_FILAS; ++i) {
        for (int j = 0; j < NUM_COLUMNAS; ++j) {
            if (estado.tablero[i][j] == estado.jugador_actual)
                puntaje_jugador++;
            else if (estado.tablero[i][j] != 0)
                puntaje_oponente++;
        }
    }
    return puntaje_jugador - puntaje_oponente;
}
