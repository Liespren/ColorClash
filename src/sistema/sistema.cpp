#include "sistema.h"
#include <iostream>
using namespace std;

// Constructor: inicializa tablero, jugadores y conecta punteros
Sistema::Sistema()
    : turnoActual(1), maxTurnos(2), jugador1("R", "rojo"), jugador2("A", "azul")
{
    // Inicializar tablero con casillas blancas sin jugadores
    for (int i = 0; i < 5; ++i)
        for (int j = 0; j < 5; ++j)
            tablero[i][j] = Casilla("blanco", nullptr);

    // Conectar punteros (nexos) entre casillas
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

    // Asignar posiciones iniciales a jugadores
    tablero[0][0].setJugador(&jugador1);
    tablero[0][0].setColor(jugador1.getColor());

    tablero[4][4].setJugador(&jugador2);
    tablero[4][4].setColor(jugador2.getColor());
}

void Sistema::iniciarJuego() {
    cout << "Iniciando juego..." << endl;
    imprimirEstadoTablero();
}

void Sistema::imprimirEstadoTablero() {
    cout << "Tablero:" << endl;

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
}

void Sistema::ejecutarTurno() {
    cout << "\nTurno " << turnoActual << endl;

    // Ejecutar acciones para jugador1 y jugador2, alternando turnos si quieres
    ejecutarAccionesJugador(jugador1);
    ejecutarAccionesJugador(jugador2);

    // Imprimir el estado actual del tablero
    imprimirEstadoTablero();

    turnoActual++;
}

void Sistema::ejecutarAccionesJugador(Jugador& jugador) {
    jugador.setAcciones(2);

    cout << "\nTurno de " << jugador.getNombre() << endl;

    while (jugador.getAcciones() > 0) {
        cout << "Acciones restantes: " << jugador.getAcciones() << endl;
        cout << "1) Mover\n2) Pintar\nElige accion: ";
        string accion;
        cin >> accion;

        char dir = ' ';
        if (accion == "1" || accion == "2") {
            cout << "Elige direccion (W=Arriba, S=Abajo, A=Izquierda, D=Derecha): ";
            char opcion;
            cin >> opcion;
            opcion = tolower(opcion);

            switch (opcion) {
                case 'w': dir = 'U'; break;
                case 's': dir = 'D'; break;
                case 'a': dir = 'L'; break;
                case 'd': dir = 'R'; break;
                default:
                    cout << "Direccion invalida. Intenta de nuevo.\n";
                    continue;
            }
        } else {
            cout << "Accion invalida. Intenta de nuevo.\n";
            continue;
        }

        bool exito = false;
        if (accion == "1") {
            exito = moverJugador(jugador, dir);
        } else if (accion == "2") {
            exito = pintarCasilla(jugador, dir);
        }

        if (exito) {
            jugador.setAcciones(jugador.getAcciones() - 1);
        } else {
            cout << "No se pudo realizar la accion. Intenta otra vez.\n";
        }
    }
}

bool Sistema::moverJugador(Jugador& jugador, char dir) {
    // Encontrar la casilla actual del jugador
    Casilla* casillaActual = nullptr;
    for (int i = 0; i < 5; ++i)
        for (int j = 0; j < 5; ++j)
            if (tablero[i][j].getJugador() == &jugador)
                casillaActual = &tablero[i][j];

    if (!casillaActual) {
        cout << "Error: jugador no esta en el tablero.\n";
        return false;
    }

    Casilla* destino = nullptr;
    switch (dir) {
        case 'U': destino = casillaActual->getPtrU(); break;
        case 'D': destino = casillaActual->getPtrD(); break;
        case 'L': destino = casillaActual->getPtrL(); break;
        case 'R': destino = casillaActual->getPtrR(); break;
        default: return false;
    }

    if (destino == nullptr) {
        cout << "No se puede mover en esa direccion (fuera del tablero).\n";
        return false;
    }

    if (destino->getJugador() != nullptr) {
        cout << "Casilla ocupada, no se puede mover ahi.\n";
        return false;
    }

    // Mover jugador
    destino->setJugador(&jugador);
    destino->setColor(jugador.getColor());
    casillaActual->setJugador(nullptr);
    casillaActual->setColor("blanco");

    cout << "Jugador movido correctamente.\n";
    return true;
}

bool Sistema::pintarCasilla(Jugador& jugador, char dir) {
    // Encontrar la casilla actual del jugador
    Casilla* casillaActual = nullptr;
    for (int i = 0; i < 5; ++i)
        for (int j = 0; j < 5; ++j)
            if (tablero[i][j].getJugador() == &jugador)
                casillaActual = &tablero[i][j];

    if (!casillaActual) {
        cout << "Error: jugador no esta en el tablero.\n";
        return false;
    }

    Casilla* destino = nullptr;
    switch (dir) {
        case 'U': destino = casillaActual->getPtrU(); break;
        case 'D': destino = casillaActual->getPtrD(); break;
        case 'L': destino = casillaActual->getPtrL(); break;
        case 'R': destino = casillaActual->getPtrR(); break;
        default: return false;
    }

    if (destino == nullptr) {
        cout << "No se puede pintar en esa direccion (fuera del tablero).\n";
        return false;
    }

    destino->setColor(jugador.getColor());
    cout << "Casilla pintada correctamente.\n";
    return true;
}

bool Sistema::juegoTerminado() const {
    return turnoActual > maxTurnos;
}
