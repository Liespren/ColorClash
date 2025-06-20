/*
 * IA.H - INTELIGENCIA ARTIFICIAL DEL JUEGO
 * 
 * DESCRIPCIÓN:
 * Esta clase implementa la inteligencia artificial del juego ColorClash
 * utilizando el algoritmo minimax con poda alfa-beta para tomar decisiones
 * óptimas en cada turno.
 * 
 * FUNCIONALIDADES:
 * - Algoritmo minimax con optimizaciones
 * - Generación inteligente de movimientos
 * - Evaluación estratégica de posiciones
 * - Sistema de búsqueda en profundidad
 * 
 */

#pragma once

#include <vector>
#include <limits>
using namespace std;

const int NUM_FILAS = 5; 
const int NUM_COLUMNAS = 5;

// Estructura que representa un movimiento o acción en el juego
struct Movimiento {
    int fila;           // Fila de destino del movimiento
    int columna;        // Columna de destino del movimiento
    bool es_pintura;    // true si es acción de pintar, false si es mover

    // Constructor con parámetros opcionales
    Movimiento(int f, int c, bool p = false) : fila(f), columna(c), es_pintura(p) {}
};

// Estructura que representa el estado completo del tablero
struct Estado {
    int tablero[NUM_FILAS][NUM_COLUMNAS];  // Estado del tablero (0=vacía, 1=jugador1, 2=jugador2)
    int jugador_actual;                    // Jugador que tiene el turno (1 o 2)

    // Constructor: crea estado a partir de un tablero existente
    Estado(int original[NUM_FILAS][NUM_COLUMNAS], int turno_actual);
    
    // Constructor de copia: duplica un estado existente
    Estado(const Estado& otro);
};

class IA {
public:
    // Constructor: inicializa la IA con profundidad máxima de búsqueda
    IA(int profundidad_maxima);

    // Método principal: calcula el mejor movimiento para el jugador actual
    Movimiento obtener_mejor_movimiento(int tablero[NUM_FILAS][NUM_COLUMNAS], int jugador);

private:
    int profundidad;    // Profundidad máxima de búsqueda del algoritmo

    // Algoritmo minimax con poda alfa-beta
    int minimax(Estado estado, int profundidad_actual, int alpha, int beta, bool es_maximizador);

    // Genera todos los movimientos válidos desde un estado dado
    vector<Movimiento> generar_movimientos_validos(const Estado& estado);

    // Aplica un movimiento a un estado y devuelve el nuevo estado
    Estado aplicar_movimiento(const Estado& estado, const Movimiento& mov);

    // Evalúa la calidad de un estado del tablero
    int evaluar(const Estado& estado);

    // Verifica si un movimiento es válido en un estado dado
    bool es_movimiento_valido(const Estado& estado, const Movimiento& mov) const;

    // Evalúa el valor estratégico de una posición específica
    int evaluar_posicion_estrategica(int fila, int col) const;
};
