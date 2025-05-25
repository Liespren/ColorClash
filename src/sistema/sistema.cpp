#include "sistema.h"
#include <iostream>
using namespace std;

Sistema::Sistema()
    : turnoActual(1), maxTurnos(10), jugador1("Jugador 1", "rojo"), jugador2("Jugador 2", "azul")
{
    // Inicializa cada casilla del tablero con color blanco y sin jugador
    for (int i = 0; i < 5; ++i) {
        for (int j = 0; j < 5; ++j) {
            tablero[i][j] = Casilla("blanco", nullptr);
        }
    }

    // Conecta punteros (nexos) entre casillas
    for (int i = 0; i < 5; ++i) {
        for (int j = 0; j < 5; ++j) {
            if (i > 0)
                tablero[i][j].setPtrU(&tablero[i - 1][j]);
            if (i < 4)
                tablero[i][j].setPtrD(&tablero[i + 1][j]);
            if (j > 0)
                tablero[i][j].setPtrL(&tablero[i][j - 1]);
            if (j < 4)
                tablero[i][j].setPtrR(&tablero[i][j + 1]);
        }
    }

    // Asigna jugador 1 a la casilla (0,0)
    tablero[0][0].setJugador(&jugador1);
    tablero[0][0].setColor(jugador1.getColor());

    // Asigna jugador 2 a la casilla (4,4)
    tablero[4][4].setJugador(&jugador2);
    tablero[4][4].setColor(jugador2.getColor());
}

void Sistema::imprimirIniciarSistema() {
    cout << "¡Bienvenido a ColorClash!" << endl;
}

void Sistema::iniciarJuego() {
    cout << "Iniciando juego..." << endl;
    // Puedes agregar lógica adicional aquí si es necesario
}

void Sistema::ejecutarTurno() {
    cout << "\nTurno " << turnoActual << " del jugador." << endl;
    cout << "Estado del tablero:" << endl;

    for (int i = 0; i < 5; ++i) {
        for (int j = 0; j < 5; ++j) {
            // Mostrar color
            cout << tablero[i][j].getColor();

            // Mostrar jugador si hay uno
            Jugador* jugadorEnCasilla = tablero[i][j].getJugador();
            if (jugadorEnCasilla != nullptr) {
                cout << "(" << jugadorEnCasilla->getNombre() << ")";
            }
            cout << "\t";
        }
        cout << endl;
    }

    turnoActual++;
}

bool Sistema::juegoTerminado() const {
    return turnoActual > maxTurnos;
}
