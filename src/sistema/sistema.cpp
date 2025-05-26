#include <iostream>
#include "sistema.h"

#ifdef _WIN32
#include <windows.h>
#ifndef ENABLE_VIRTUAL_TERMINAL_PROCESSING
#define ENABLE_VIRTUAL_TERMINAL_PROCESSING 0x0004
#endif
#endif
using namespace std;

// Constructor: inicializa tablero, jugadores y conecta punteros
Sistema::Sistema()
    : turnoActual(1), maxTurnos(5), jugador1("R", "rojo"), jugador2("A", "azul")
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
    tablero[1][1].setJugador(&jugador1);
    tablero[1][1].setColor(jugador1.getColor());

    tablero[3][3].setJugador(&jugador2);
    tablero[3][3].setColor(jugador2.getColor());
}

void Sistema::iniciarJuego() {
    cout << "Iniciando juego..." << endl;
    imprimirEstadoTablero();
}

void Sistema::habilitarColoresANSI() {
#ifdef _WIN32
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    if (hOut != INVALID_HANDLE_VALUE) {
        DWORD dwMode = 0;
        if (GetConsoleMode(hOut, &dwMode)) {
            dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
            SetConsoleMode(hOut, dwMode);
        }
    }
#endif
}

void Sistema::imprimirEstadoTablero() {
    habilitarColoresANSI();

    int puntosRojo = 0;
    int puntosAzul = 0;

    cout << "\n    ";
    for (int col = 0; col < 5; ++col) {
        cout << col << "     ";
    }
    cout << "\n  +-----+-----+-----+-----+-----+\n";

    for (int i = 0; i < 5; ++i) {
        cout << i << " |";
        for (int j = 0; j < 5; ++j) {
            string color = tablero[i][j].getColor();
            if (color == "rojo") puntosRojo++;
            else if (color == "azul") puntosAzul++;

            Jugador* jugadorEnCasilla = tablero[i][j].getJugador();
            string contenido = "     ";
            if (jugadorEnCasilla != nullptr) {
                contenido = "  " + jugadorEnCasilla->getNombre() + "  ";
            }

            // Colorear fondo según el color de la casilla
            if (color == "rojo")
                cout << "\033[41m" << contenido << "\033[0m|";
            else if (color == "azul")
                cout << "\033[44m" << contenido << "\033[0m|";
            else
                cout << "\033[47m" << contenido << "\033[0m|";
        }
        cout << "\n  +-----+-----+-----+-----+-----+\n";
    }

    cout << "\nPuntaje:\n";
    cout << "Rojo (R): " << puntosRojo << " puntos\n";
    cout << "Azul (A): " << puntosAzul << " puntos\n";

    if (turnoActual >= maxTurnos) {
        if (puntosRojo == puntosAzul) {
            cout << "\nEmpate! Se añade un turno adicional.\n";
            maxTurnos++;
        } else {
            cout << "\n=== Juego terminado ===\n";
            if (puntosRojo > puntosAzul)
                cout << "Jugador Rojo (R) gana!\n";
            else
                cout << "Jugador Azul (A) gana!\n";
        }
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
    // Aplicar penalización si corresponde
    if (jugador.getPenalizaciones() > 0) {
        cout << jugador.getNombre() << " tiene una penalizacion y pierde 1 accion este turno.\n";
        jugador.setAcciones(1);
        jugador.setPenalizaciones(0);
    } else {
        jugador.setAcciones(2);
    }

    cout << "\nTurno de " << jugador.getNombre() << endl;

    while (jugador.getAcciones() > 0) {
        cout << "Acciones restantes: " << jugador.getAcciones() << endl;
        cout << "1) Mover\n2) Pintar\nElige accion: ";
        string accion;
        cin >> accion;

        char dir = ' ';
        if (accion == "1" || accion == "2") {
            cout << "Elige direccion (WASD): ";
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

            // Si la pintura fue exitosa, verificamos si hay un jugador en esa casilla
            if (exito) {
                Casilla* casillaPintada = obtenerCasillaEnDireccion(jugador, dir);
                if (casillaPintada != nullptr) {
                    Jugador* jugadorEnCasilla = casillaPintada->getJugador();
                    if (jugadorEnCasilla != nullptr && jugadorEnCasilla != &jugador) {
                        jugadorEnCasilla->incrementarPenalizaciones(1);
                        cout << "¡El rival " << jugadorEnCasilla->getNombre()
                             << " fue pintado en su casilla! Pierde 1 accion en su proximo turno.\n";
                    }
                }
            }
        }

        if (exito) {
            jugador.setAcciones(jugador.getAcciones() - 1);
        } else {
            cout << "No se pudo realizar la accion. Intenta otra vez.\n";
        }
        cout << endl;
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

Casilla* Sistema::obtenerCasillaEnDireccion(Jugador& jugador, char dir) {
    int filaJugador = -1;
    int colJugador = -1;

    // Buscar la posición actual del jugador en el tablero
    for (int i = 0; i < 5; ++i) {
        for (int j = 0; j < 5; ++j) {
            if (tablero[i][j].getJugador() == &jugador) {
                filaJugador = i;
                colJugador = j;
                break;
            }
        }
        if (filaJugador != -1) break;
    }

    if (filaJugador == -1 || colJugador == -1) {
        return nullptr;  // No se encontró al jugador
    }

    // Calcular la dirección
    int nuevaFila = filaJugador;
    int nuevaCol = colJugador;

    switch (dir) {
        case 'U': nuevaFila -= 1; break;
        case 'D': nuevaFila += 1; break;
        case 'L': nuevaCol -= 1; break;
        case 'R': nuevaCol += 1; break;
        default: return nullptr;
    }

    // Validar límites del tablero
    if (nuevaFila >= 0 && nuevaFila < 5 && nuevaCol >= 0 && nuevaCol < 5) {
        return &tablero[nuevaFila][nuevaCol];
    }

    return nullptr;  // Dirección fuera de los límites
}

bool Sistema::juegoTerminado() const {
    return turnoActual > maxTurnos;
}
