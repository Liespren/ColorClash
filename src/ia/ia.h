#pragma once
#include <vector>
#include <utility> // std::pair
#include <string>

using namespace std;

struct MovimientoIA {
    string direccion;
    float puntaje;
    vector<pair<int, int>> casillasParaPintar;
};

class Sistema;  // Forward declaration para evitar inclusión circular

class IA {
public:
    IA();

    // Devuelve el mejor movimiento posible para la IA, dado su posición actual
    MovimientoIA mejorMovimientoParaIA(int filaActual, int colActual, const Sistema& sistema);

private:
    // Funciones auxiliares (puedes agregar más según necesites)
    vector<pair<int,int>> obtenerAdyacentes(int fila, int col, int maxFilas = 5, int maxCols = 5) const;
    float evaluarCasillaParaIA(int fila, int col, const Sistema& sistema) const;
};
