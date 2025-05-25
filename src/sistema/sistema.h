#pragma once
#include "../casilla/casilla.h"
#include "../jugador/jugador.h"

class Sistema {
private:
    Casilla tablero[5][5];
    int turnoActual;
    int maxTurnos;
    Jugador jugador1;
    Jugador jugador2;

public:
    Sistema();

    void imprimirIniciarSistema();
    void iniciarJuego();
    void ejecutarTurno();
    bool juegoTerminado() const;
};
