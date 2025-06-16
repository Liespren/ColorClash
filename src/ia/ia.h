#pragma once

#include <vector>
#include <limits>
using namespace std;

const int NUM_FILAS = 5; 
const int NUM_COLUMNAS = 5;

struct Movimiento {
    int fila;
    int columna;
    bool es_pintura;  // true si es una accion de pintar, false si es mover

    Movimiento(int f, int c, bool p = false) : fila(f), columna(c), es_pintura(p) {}
};

struct Estado {
    int tablero[NUM_FILAS][NUM_COLUMNAS];
    int jugador_actual;

    Estado(int original[NUM_FILAS][NUM_COLUMNAS], int turno_actual);
    Estado(const Estado& otro);  // Copy constructor
};

class IA {
public:
    IA(int profundidad_maxima);

    Movimiento obtener_mejor_movimiento(int tablero[NUM_FILAS][NUM_COLUMNAS], int jugador);

private:
    int profundidad;

    int minimax(Estado estado, int profundidad_actual, int alpha, int beta, bool es_maximizador);

    vector<Movimiento> generar_movimientos_validos(const Estado& estado);

    Estado aplicar_movimiento(const Estado& estado, const Movimiento& mov);

    int evaluar(const Estado& estado);

    bool es_movimiento_valido(const Estado& estado, const Movimiento& mov) const;

    int evaluar_posicion_estrategica(int fila, int col) const;
};
