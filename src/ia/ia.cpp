/*
 * IA.CPP - IMPLEMENTACIÓN DE LA INTELIGENCIA ARTIFICIAL
 * 
 * DESCRIPCIÓN:
 * Implementación de la clase IA que utiliza el algoritmo minimax con
 * poda alfa-beta para tomar decisiones óptimas en el juego ColorClash.
 * 
 * FUNCIONALIDADES PRINCIPALES:
 * - Algoritmo minimax con optimizaciones de poda
 * - Generación inteligente y priorizada de movimientos
 * - Evaluación estratégica de posiciones del tablero
 * - Sistema de búsqueda en profundidad configurable
 * 
 */

#include "ia.h"
#include <algorithm>
#include <random>
#include <chrono>

// CONSTRUCTORES DE LA ESTRUCTURA ESTADO

// Constructor: crea un estado a partir de un tablero existente
Estado::Estado(int original[NUM_FILAS][NUM_COLUMNAS], int turno_actual) {
    jugador_actual = turno_actual;
    // Copiar el estado del tablero
    for (int i = 0; i < NUM_FILAS; ++i) {
        for (int j = 0; j < NUM_COLUMNAS; ++j) {
            tablero[i][j] = original[i][j];
        }
    }
}

// Constructor de copia: duplica un estado existente
Estado::Estado(const Estado& otro) {
    jugador_actual = otro.jugador_actual;
    // Copiar el estado del tablero
    for (int i = 0; i < NUM_FILAS; ++i) {
        for (int j = 0; j < NUM_COLUMNAS; ++j) {
            tablero[i][j] = otro.tablero[i][j];
        }
    }
}

// CONSTRUCTOR DE LA CLASE IA

// Inicializa la IA con la profundidad máxima de búsqueda
IA::IA(int profundidad_maxima) {
    profundidad = profundidad_maxima;
}

// MÉTODO PRINCIPAL - CÁLCULO DEL MEJOR MOVIMIENTO

// Calcula el mejor movimiento posible para el jugador actual
Movimiento IA::obtener_mejor_movimiento(int tablero[NUM_FILAS][NUM_COLUMNAS], int jugador) {
    Estado estado_inicial(tablero, jugador);
    Movimiento mejor_movimiento = {-1, -1};  // Movimiento inválido por defecto
    int mejor_valor = numeric_limits<int>::min();

    // Generar todos los movimientos válidos
    vector<Movimiento> movimientos = generar_movimientos_validos(estado_inicial);
    if (movimientos.empty()) {
        return mejor_movimiento;  // No hay movimientos válidos
    }

    // Evaluar cada movimiento usando minimax
    for (Movimiento mov : movimientos) {
        if (!es_movimiento_valido(estado_inicial, mov)) continue;
        
        Estado nuevo_estado = aplicar_movimiento(estado_inicial, mov);
        int valor = minimax(nuevo_estado, profundidad - 1, numeric_limits<int>::min(), numeric_limits<int>::max(), false);
        
        // Actualizar el mejor movimiento si encontramos uno mejor
        if (valor > mejor_valor) {
            mejor_valor = valor;
            mejor_movimiento = mov;
        }
    }
    return mejor_movimiento;
}

// ALGORITMO MINIMAX CON PODA ALFA-BETA

// Implementación del algoritmo minimax con optimizaciones
int IA::minimax(Estado estado, int profundidad_actual, int alpha, int beta, bool es_maximizador) {
    // Condición de parada: profundidad máxima alcanzada o sin movimientos
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
            if (beta <= alpha) break; // Poda beta
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
            if (beta <= alpha) break; // Poda alfa
        }
        return min_eval;
    }
}

// GENERACIÓN DE MOVIMIENTOS

// Genera todos los movimientos válidos desde un estado dado
vector<Movimiento> IA::generar_movimientos_validos(const Estado& estado) {
    vector<Movimiento> movimientos;
    bool visitado[NUM_FILAS][NUM_COLUMNAS] = {false};

    // Crear generador de números aleatorios para evitar sesgo
    unsigned seed = chrono::system_clock::now().time_since_epoch().count();
    default_random_engine generator(seed);

    // Encontrar la posición del oponente para estrategia
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

    // Recorrer el tablero buscando el jugador actual
    for (int i = 0; i < NUM_FILAS; ++i) {
        for (int j = 0; j < NUM_COLUMNAS; ++j) {
            if (estado.tablero[i][j] == estado.jugador_actual) {
                // Definir direcciones posibles (arriba, abajo, izquierda, derecha)
                vector<pair<int,int>> dirs = {
                    {-1,0},  // Arriba
                    {1,0},   // Abajo
                    {0,-1},  // Izquierda
                    {0,1}    // Derecha
                };
                
                // Mezclar direcciones para evitar patrones predecibles
                shuffle(dirs.begin(), dirs.end(), generator);

                // Estrategia: priorizar movimientos hacia el oponente si está cerca
                if (fila_oponente != -1) {
                    int dist_actual = abs(i - fila_oponente) + abs(j - col_oponente);
                    if (dist_actual <= 2) {  // Si estamos a 2 casillas o menos
                        // Ordenar direcciones para priorizar acercamiento al oponente
                        sort(dirs.begin(), dirs.end(), [&](const pair<int,int>& a, const pair<int,int>& b) {
                            int dist_a = abs((i + a.first) - fila_oponente) + abs((j + a.second) - col_oponente);
                            int dist_b = abs((i + b.first) - fila_oponente) + abs((j + b.second) - col_oponente);
                            return dist_a < dist_b;
                        });
                    }
                }

                // Generar movimientos en cada dirección
                for (auto& d : dirs) {
                    int ni = i + d.first;
                    int nj = j + d.second;
                    if (ni >= 0 && ni < NUM_FILAS && nj >= 0 && nj < NUM_COLUMNAS && !visitado[ni][nj]) {
                        // Considerar movimiento si la casilla está vacía
                        if (estado.tablero[ni][nj] == 0) {
                            movimientos.push_back(Movimiento(ni, nj, false));  // Movimiento
                            visitado[ni][nj] = true;
                        }
                        // Considerar pintar si la casilla no es del jugador actual
                        if (estado.tablero[ni][nj] != estado.jugador_actual) {
                            // Priorizar pintar si estamos adyacentes al oponente
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

// APLICACIÓN DE MOVIMIENTOS

// Aplica un movimiento a un estado y devuelve el nuevo estado
Estado IA::aplicar_movimiento(const Estado& estado, const Movimiento& mov) {
    Estado nuevo_estado = estado;
    
    if (mov.es_pintura) {
        // Acción de pintar: cambiar el color de la casilla
        nuevo_estado.tablero[mov.fila][mov.columna] = estado.jugador_actual;
    } else {
        // Acción de mover: trasladar el jugador a la nueva posición
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
    
    // Cambiar al siguiente jugador
    nuevo_estado.jugador_actual = 3 - estado.jugador_actual; // alterna entre 1 y 2
    return nuevo_estado;
}

// VALIDACIÓN DE MOVIMIENTOS

// Verifica si un movimiento es válido en un estado dado
bool IA::es_movimiento_valido(const Estado& estado, const Movimiento& mov) const {
    // Verificar límites del tablero
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

    // Para movimientos (no pintura), la casilla destino debe estar vacía
    if (!mov.es_pintura && estado.tablero[mov.fila][mov.columna] != 0) {
        return false;
    }

    return true;
}

// EVALUACIÓN ESTRATÉGICA

// Evalúa el valor estratégico de una posición específica en el tablero
int IA::evaluar_posicion_estrategica(int fila, int col) const {
    // Dar más valor a las posiciones centrales y esquinas
    int valor = 0;
    
    // Valor central: posiciones del centro del tablero (1-3, 1-3)
    if (fila >= 1 && fila <= 3 && col >= 1 && col <= 3) {
        valor += 3;
    }
    
    // Valor esquinas: posiciones de las cuatro esquinas
    if ((fila == 0 || fila == 4) && (col == 0 || col == 4)) {
        valor += 2;
    }
    
    // Valor bordes: posiciones en los bordes del tablero
    if (fila == 0 || fila == 4 || col == 0 || col == 4) {
        valor += 1;
    }
    
    return valor;
}

// EVALUACIÓN DE ESTADOS

// Evalúa la calidad de un estado del tablero para el algoritmo minimax
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

    // Evaluar cada casilla del tablero
    for (int i = 0; i < NUM_FILAS; ++i) {
        for (int j = 0; j < NUM_COLUMNAS; ++j) {
            if (estado.tablero[i][j] == estado.jugador_actual) {
                // Puntaje base + valor estratégico de la posición
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
                // Puntaje del oponente (se resta al final)
                puntaje_oponente += 1 + evaluar_posicion_estrategica(i, j);
            } else if (estado.tablero[i][j] != 0) {
                // Bonus por tener casillas pintadas
                puntaje_jugador += 2;
            }
        }
    }
    
    // Retornar diferencia: puntaje jugador - puntaje oponente
    return puntaje_jugador - puntaje_oponente;
}
