#include "ia.h"
#include <algorithm>
#include <random>
#include <chrono>

Estado::Estado(int original[NUM_FILAS][NUM_COLUMNAS], int turno_actual) {
    jugador_actual = turno_actual;
    for (int i = 0; i < NUM_FILAS; ++i) {
        for (int j = 0; j < NUM_COLUMNAS; ++j) {
            tablero[i][j] = original[i][j];
        }
    }
}

Estado::Estado(const Estado& otro) {
    jugador_actual = otro.jugador_actual;
    for (int i = 0; i < NUM_FILAS; ++i) {
        for (int j = 0; j < NUM_COLUMNAS; ++j) {
            tablero[i][j] = otro.tablero[i][j];
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

    vector<Movimiento> movimientos = generar_movimientos_validos(estado_inicial);
    if (movimientos.empty()) {
        return mejor_movimiento;  // No hay movimientos válidos
    }

    for (Movimiento mov : movimientos) {
        if (!es_movimiento_valido(estado_inicial, mov)) continue;
        
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
            if (!es_movimiento_valido(estado, mov)) continue;
            
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
            if (!es_movimiento_valido(estado, mov)) continue;
            
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

    // Crear un generador de números aleatorios
    unsigned seed = chrono::system_clock::now().time_since_epoch().count();
    default_random_engine generator(seed);

    // Primero encontrar la posición del oponente
    int oponente = 3 - estado.jugador_actual;
    int fila_oponente = -1, col_oponente = -1;
    for (int i = 0; i < NUM_FILAS; ++i) {
        for (int j = 0; j < NUM_COLUMNAS; ++j) {
            if (estado.tablero[i][j] == oponente) {
                fila_oponente = i;
                col_oponente = j;
                break;
            }
        }
        if (fila_oponente != -1) break;
    }

    for (int i = 0; i < NUM_FILAS; ++i) {
        for (int j = 0; j < NUM_COLUMNAS; ++j) {
            if (estado.tablero[i][j] == estado.jugador_actual) {
                // Revisar vecinos en todas las direcciones
                vector<pair<int,int>> dirs = {
                    {-1,0},  // Arriba
                    {1,0},   // Abajo
                    {0,-1},  // Izquierda
                    {0,1}    // Derecha
                };
                
                // Mezclar las direcciones para evitar sesgo
                shuffle(dirs.begin(), dirs.end(), generator);

                // Si estamos cerca del oponente, priorizar movimientos hacia él
                if (fila_oponente != -1) {
                    int dist_actual = abs(i - fila_oponente) + abs(j - col_oponente);
                    if (dist_actual <= 2) {  // Si estamos a 2 casillas o menos
                        // Ordenar direcciones para priorizar las que nos acercan al oponente
                        sort(dirs.begin(), dirs.end(), [&](const pair<int,int>& a, const pair<int,int>& b) {
                            int dist_a = abs((i + a.first) - fila_oponente) + abs((j + a.second) - col_oponente);
                            int dist_b = abs((i + b.first) - fila_oponente) + abs((j + b.second) - col_oponente);
                            return dist_a < dist_b;
                        });
                    }
                }

                for (auto& d : dirs) {
                    int ni = i + d.first;
                    int nj = j + d.second;
                    if (ni >= 0 && ni < NUM_FILAS && nj >= 0 && nj < NUM_COLUMNAS && !visitado[ni][nj]) {
                        // Si la casilla está vacía, considerar movimiento
                        if (estado.tablero[ni][nj] == 0) {
                            movimientos.push_back(Movimiento(ni, nj, false));  // Movimiento
                            visitado[ni][nj] = true;
                        }
                        // Si la casilla es del oponente o está vacía, considerar pintar
                        if (estado.tablero[ni][nj] != estado.jugador_actual) {
                            // Si estamos adyacentes al oponente, priorizar pintar
                            bool es_pintura = (fila_oponente != -1 && 
                                             abs(ni - fila_oponente) + abs(nj - col_oponente) == 1);
                            movimientos.push_back(Movimiento(ni, nj, true));  // Pintar
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
    // Si es una acción de pintar, solo cambiar el color de la casilla
    if (mov.es_pintura) {
        nuevo_estado.tablero[mov.fila][mov.columna] = estado.jugador_actual;
    } else {
        // Si es un movimiento, mover el jugador
        for (int i = 0; i < NUM_FILAS; ++i) {
            for (int j = 0; j < NUM_COLUMNAS; ++j) {
                if (estado.tablero[i][j] == estado.jugador_actual) {
                    nuevo_estado.tablero[i][j] = 0;  // Limpiar posición anterior
                    break;
                }
            }
        }
        nuevo_estado.tablero[mov.fila][mov.columna] = estado.jugador_actual;
    }
    nuevo_estado.jugador_actual = 3 - estado.jugador_actual; // alterna entre 1 y 2
    return nuevo_estado;
}

bool IA::es_movimiento_valido(const Estado& estado, const Movimiento& mov) const {
    if (mov.fila < 0 || mov.fila >= NUM_FILAS || mov.columna < 0 || mov.columna >= NUM_COLUMNAS) {
        return false;
    }

    // Verificar si hay un jugador en la casilla de destino
    bool hay_jugador = false;
    for (int i = 0; i < NUM_FILAS; ++i) {
        for (int j = 0; j < NUM_COLUMNAS; ++j) {
            if (estado.tablero[i][j] == estado.jugador_actual) {
                hay_jugador = true;
                break;
            }
        }
        if (hay_jugador) break;
    }

    if (!hay_jugador) return false;

    // Si es un movimiento (no pintura), la casilla debe estar vacía
    if (!mov.es_pintura && estado.tablero[mov.fila][mov.columna] != 0) {
        return false;
    }

    return true;
}

int IA::evaluar_posicion_estrategica(int fila, int col) const {
    // Dar más valor a las posiciones centrales y esquinas
    int valor = 0;
    
    // Valor central
    if (fila >= 1 && fila <= 3 && col >= 1 && col <= 3) {
        valor += 2;
    }
    
    // Valor esquinas
    if ((fila == 0 || fila == 4) && (col == 0 || col == 4)) {
        valor += 3;
    }
    
    // Valor bordes
    if (fila == 0 || fila == 4 || col == 0 || col == 4) {
        valor += 1;
    }
    
    return valor;
}

int IA::evaluar(const Estado& estado) {
    int puntaje_jugador = 0;
    int puntaje_oponente = 0;
    int oponente = 3 - estado.jugador_actual;
    int fila_oponente = -1, col_oponente = -1;

    // Encontrar posición del oponente
    for (int i = 0; i < NUM_FILAS; ++i) {
        for (int j = 0; j < NUM_COLUMNAS; ++j) {
            if (estado.tablero[i][j] == oponente) {
                fila_oponente = i;
                col_oponente = j;
                break;
            }
        }
        if (fila_oponente != -1) break;
    }

    for (int i = 0; i < NUM_FILAS; ++i) {
        for (int j = 0; j < NUM_COLUMNAS; ++j) {
            if (estado.tablero[i][j] == estado.jugador_actual) {
                puntaje_jugador += 1 + evaluar_posicion_estrategica(i, j);
                
                // Bonus por estar cerca del oponente
                if (fila_oponente != -1) {
                    int dist = abs(i - fila_oponente) + abs(j - col_oponente);
                    if (dist == 1) {  // Adyacente al oponente
                        puntaje_jugador += 10;  // Gran bonus por estar adyacente
                    } else if (dist == 2) {  // A dos casillas
                        puntaje_jugador += 5;  // Bonus menor por estar cerca
                    }
                }
            } else if (estado.tablero[i][j] == oponente) {
                puntaje_oponente += 1 + evaluar_posicion_estrategica(i, j);
            } else if (estado.tablero[i][j] != 0) {
                // Bonus por tener casillas pintadas
                puntaje_jugador += 2;
            }
        }
    }
    return puntaje_jugador - puntaje_oponente;
}
