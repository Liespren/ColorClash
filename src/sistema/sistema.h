#pragma once
#include <iostream>
#include "../casilla/casilla.h"
using namespace std;

class Sistema {
private:
    int turnoActual;
    int maxTurnos;
    Casilla tablero[5][5];

public:
    Sistema(); 
    void imprimirIniciarSistema();
    void iniciarJuego();
    void ejecutarTurno();
    bool juegoTerminado();
};
