#include "sistema.h"
#include "../casilla/casilla.h"
#include <iostream>
using namespace std;

// Constructor
Sistema::Sistema() : turnoActual(1), maxTurnos(10) {
    // Inicializa cada casilla del tablero con valores por defecto
    for (int i = 0; i < 5; ++i) {
        for (int j = 0; j < 5; ++j) {
            tablero[i][j] = Casilla("blanco", "ninguno");
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
}

// Muestra mensaje inicial
void Sistema::imprimirIniciarSistema() {
    cout << "¡Bienvenido a ColorClash!" << endl;
}

// Inicializa el juego
void Sistema::iniciarJuego() {
    cout << "Iniciando juego..." << endl;
    // Podrías agregar lógica adicional aquí si lo necesitas
}

// Ejecuta un turno y muestra el estado del tablero
void Sistema::ejecutarTurno() {
    cout << "\nTurno " << turnoActual << " del jugador." << endl;
    cout << "Estado del tablero:" << endl;

    for (int i = 0; i < 5; ++i) {
        for (int j = 0; j < 5; ++j) {
            cout << tablero[i][j].getColor() << "\t";
        }
        cout << endl;
    }

    turnoActual++;
}

// Verifica si el juego terminó
bool Sistema::juegoTerminado() {
    return turnoActual > maxTurnos;
}
