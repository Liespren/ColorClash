#include "sistema.h"
#include <iostream>
using namespace std;

Sistema::Sistema() : turnoActual(1), maxTurnos(10) {}

void Sistema::iniciarJuego() {
    cout << "Iniciando el sistema del juego..." << endl;
}

void Sistema::ejecutarTurno() {
    cout << "Turno " << turnoActual << " del jugador." << endl;
    turnoActual++;
}

bool Sistema::juegoTerminado() const {
    return turnoActual > maxTurnos;
}

void Sistema::imprimirIniciarSistema() {
    cout << "Iniciando Sistema" << endl;
}
