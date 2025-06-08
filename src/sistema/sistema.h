#pragma once

#include "../casilla/casilla.h"
#include "../jugador/jugador.h"
#include <iostream>

class Sistema {
private:
    Casilla tablero[5][5];
    int turnoActual;
    int maxTurnos;
    Jugador jugador1;
    Jugador jugador2;

public:
    Sistema();

    void habilitarColoresANSI();

    void iniciarJuego();
    void ejecutarTurno();
    void ejecutarAccionesJugador(Jugador& jugador);
    void imprimirEstadoTablero();
    
    bool moverJugador(Jugador& jugador, char dir);
    bool pintarCasilla(Jugador& jugador, char dir);

    Casilla* obtenerCasillaEnDireccion(Jugador& jugador, char dir);
    char obtenerColorCasilla(int fila, int col) const;

    void ejecutarTurnoIA(Jugador& jugador);

    bool juegoTerminado() const;
};
