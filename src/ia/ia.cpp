#include "ia.h"
#include "../sistema/sistema.h"  // Incluye para acceder a Sistema
#include <string>
#include <algorithm>

using namespace std;

IA::IA() {}

vector<pair<int,int>> IA::obtenerAdyacentes(int fila, int col, int maxFilas, int maxCols) const {
    vector<pair<int,int>> adyacentes;
    const int dx[] = {-1, 1, 0, 0};
    const int dy[] = {0, 0, -1, 1};

    for (int i = 0; i < 4; ++i) {
        int nf = fila + dx[i];
        int nc = col + dy[i];
        if (nf >= 0 && nf < maxFilas && nc >= 0 && nc < maxCols) {
            adyacentes.emplace_back(nf, nc);
        }
    }
    return adyacentes;
}

float IA::evaluarCasillaParaIA(int fila, int col, const Sistema& sistema) const {
    // preferir casillas vacías o propias, penalizar casillas del oponente
    // Aquí necesitas acceder a sistema.tablero para evaluar, pero si tablero es privado, crea un método público en Sistema para obtener info de casillas

    // Supongamos que Sistema tiene un método: char obtenerColorCasilla(int fila, int col);
    char color = sistema.obtenerColorCasilla(fila, col);

    if (color == 'A') return 0.0f; // Ya pintado por IA (azul), no pintar
    if (color == 'R') return -1.0f; // Pintado por rival, menos preferible
    return 1.0f; // Casilla vacía, preferible
}

MovimientoIA IA::mejorMovimientoParaIA(int filaActual, int colActual, const Sistema& sistema) {
    vector<string> direcciones = {"quieto", "arriba", "abajo", "izquierda", "derecha"};
    const int dx[] = {0, -1, 1, 0, 0};
    const int dy[] = {0, 0, 0, -1, 1};

    MovimientoIA mejorMovimiento = {"quieto", -1000.0f, {}};

    for (int i = 0; i < 5; ++i) {
        int nf = filaActual + dx[i];
        int nc = colActual + dy[i];

        // Si no es "quieto", validar límites
        if (i != 0 && (nf < 0 || nf >= 5 || nc < 0 || nc >= 5)) continue;

        vector<pair<int,int>> adyacentes = obtenerAdyacentes(nf, nc);

        float puntajeTotal = 0.0f;
        vector<pair<int,int>> casillasParaPintar;

        for (auto& casilla : adyacentes) {
            float p = evaluarCasillaParaIA(casilla.first, casilla.second, sistema);
            if (p > 0) {  // Solo pintar casillas positivas
                puntajeTotal += p;
                casillasParaPintar.push_back(casilla);
                if (casillasParaPintar.size() >= 2) break; // máximo 2 casillas para pintar
            }
        }

        if (puntajeTotal > mejorMovimiento.puntaje) {
            mejorMovimiento.direccion = direcciones[i];
            mejorMovimiento.puntaje = puntajeTotal;
            mejorMovimiento.casillasParaPintar = casillasParaPintar;
        }
    }

    return mejorMovimiento;
}
