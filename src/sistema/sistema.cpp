/*
 * SISTEMA.CPP - IMPLEMENTACIÓN DEL CONTROLADOR PRINCIPAL
 * 
 * DESCRIPCIÓN:
 * Implementación de la clase Sistema que controla toda la lógica del juego.
 * Incluye la inicialización del tablero, gestión de turnos, validación de
 * movimientos y la interfaz de usuario.
 * 
 * FUNCIONALIDADES PRINCIPALES:
 * - Inicialización del tablero con sistema de punteros
 * - Gestión de turnos y acciones de jugadores
 * - Validación y ejecución de movimientos
 * - Sistema de pintura y penalizaciones
 * - Visualización con colores ANSI
 * - Integración con la IA
 * 
 */

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
Sistema::Sistema():
    turnoActual(1), 
    maxTurnos(5), 
    jugador1("R", "rojo"), 
    jugador2("A", "azul"),
    ia(5)
{
    // Inicializar tablero con casillas blancas sin jugadores
    for (int i = 0; i < 5; ++i)
        for (int j = 0; j < 5; ++j)
            tablero[i][j] = Casilla("blanco", nullptr);

    // Conectar punteros (nexos) entre casillas para navegación eficiente
    for (int i = 0; i < 5; ++i) {
        for (int j = 0; j < 5; ++j) {
            if (i > 0)
                tablero[i][j].setPtrU(&tablero[i - 1][j]);  // Puntero arriba
            if (i < 4)
                tablero[i][j].setPtrD(&tablero[i + 1][j]);  // Puntero abajo
            if (j > 0)
                tablero[i][j].setPtrL(&tablero[i][j - 1]);  // Puntero izquierda
            if (j < 4)
                tablero[i][j].setPtrR(&tablero[i][j + 1]);  // Puntero derecha
        }
    }

    // Asignar posiciones iniciales a jugadores
    tablero[1][1].setJugador(&jugador1);  // Jugador rojo en posición (1,1)
    tablero[1][1].setColor(jugador1.getColor());

    tablero[3][3].setJugador(&jugador2);  // Jugador azul en posición (3,3)
    tablero[3][3].setColor(jugador2.getColor());
}

// Inicia el juego e imprime el estado inicial
void Sistema::iniciarJuego() {
    cout << "Iniciando juego..." << endl;
    imprimirEstadoTablero();
}

// Habilita colores ANSI para Windows (necesario para mostrar colores en consola)
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

// Imprime el estado actual del tablero con colores y puntuaciones
void Sistema::imprimirEstadoTablero() {
    habilitarColoresANSI();

    int puntosRojo = 0;
    int puntosAzul = 0;

    // Imprimir coordenadas de columnas
    cout << "\n    ";
    for (int col = 0; col < 5; ++col) {
        cout << col << "     ";
    }
    cout << "\n  +-----+-----+-----+-----+-----+\n";

    // Imprimir filas del tablero con colores
    for (int i = 0; i < 5; ++i) {
        cout << i << " |";
        for (int j = 0; j < 5; ++j) {
            string color = tablero[i][j].getColor();
            // Contar puntos por color
            if (color == "rojo") puntosRojo++;
            else if (color == "azul") puntosAzul++;

            Jugador* jugadorEnCasilla = tablero[i][j].getJugador();
            string contenido = "     ";
            if (jugadorEnCasilla != nullptr) {
                contenido = "  " + jugadorEnCasilla->getNombre() + "  ";
            }

            // Aplicar colores ANSI según el color de la casilla
            if (color == "rojo")
                cout << "\033[30;41m" << contenido << "\033[0m|";  // texto negro, fondo rojo
            else if (color == "azul")
                cout << "\033[30;44m" << contenido << "\033[0m|";  // texto negro, fondo azul
            else
                cout << "\033[30;47m" << contenido << "\033[0m|";  // texto negro, fondo blanco
        }
        cout << "\n  +-----+-----+-----+-----+-----+\n";
    }

    // Mostrar puntuaciones
    cout << "\nPuntaje:\n";
    cout << "Rojo (R): " << puntosRojo << " puntos\n";
    cout << "Azul (A): " << puntosAzul << " puntos\n";

    // Verificar fin de juego o empate
    if (turnoActual >= maxTurnos) {
        if (puntosRojo == puntosAzul) {
            cout << "\nEmpate! Se agrega un turno adicional.\n";
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

// Ejecuta un turno completo: jugador humano + IA
void Sistema::ejecutarTurno() {
    cout << "\nTurno " << turnoActual << endl;

    // Ejecutar acciones para jugador humano y IA
    ejecutarAccionesJugador(jugador1);
    ejecutarTurnoIA(jugador2);

    // Imprimir el estado actual del tablero
    imprimirEstadoTablero();

    turnoActual++;
}

// Gestiona las acciones del jugador humano durante su turno
void Sistema::ejecutarAccionesJugador(Jugador& jugador) {
    // Aplicar penalización si corresponde (por ser pintado en turno anterior)
    if (jugador.getPenalizaciones() > 0) {
        cout << jugador.getNombre() << " tiene una penalizacion y pierde 1 accion este turno.\n";
        jugador.setAcciones(1);  // Solo 1 acción en lugar de 2
        jugador.setPenalizaciones(0);  // Resetear penalización
    } else {
        jugador.setAcciones(2);  // Acciones normales
    }

    cout << "\nTurno de " << jugador.getNombre() << endl;

    // Bucle de acciones del jugador
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

            // Convertir WASD a direcciones internas
            switch (opcion) {
                case 'w': dir = 'U'; break;  // Arriba
                case 's': dir = 'D'; break;  // Abajo
                case 'a': dir = 'L'; break;  // Izquierda
                case 'd': dir = 'R'; break;  // Derecha
                default:
                    cout << "Direccion invalida. Intenta de nuevo.\n";
                    continue;
            }
        } else {
            cout << "Accion invalida. Intenta de nuevo.\n";
            continue;
        }

        // Ejecutar la acción seleccionada
        bool exito = false;
        if (accion == "1") {
            exito = moverJugador(jugador, dir);
        } else if (accion == "2") {
            exito = pintarCasilla(jugador, dir);

            // Verificar si se pintó al oponente (aplicar penalización)
            if (exito) {
                Casilla* casillaPintada = obtenerCasillaEnDireccion(jugador, dir);
                if (casillaPintada != nullptr) {
                    Jugador* jugadorEnCasilla = casillaPintada->getJugador();
                    if (jugadorEnCasilla != nullptr && jugadorEnCasilla != &jugador) {
                        jugadorEnCasilla->incrementarPenalizaciones(1);
                        cout << "El rival " << jugadorEnCasilla->getNombre()
                             << " fue pintado en su casilla! Pierde 1 accion en su proximo turno.\n";
                    }
                }
            }
        }

        // Actualizar acciones restantes
        if (exito) {
            jugador.setAcciones(jugador.getAcciones() - 1);
        } else {
            cout << "No se pudo realizar la accion. Intenta otra vez.\n";
        }
        cout << endl;
    }
}

// Mueve un jugador en la dirección especificada
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
    casillaActual->setJugador(nullptr);

    cout << "Jugador movido correctamente.\n";
    return true;
}

// Pinta una casilla adyacente en la dirección especificada
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

    // Si la casilla ya es del color del jugador, no hacer nada
    if (destino->getColor() == jugador.getColor()) {
        cout << "La casilla ya es de tu color.\n";
        return false;
    }

    // Si la casilla era de otro color, decrementar el contador del otro jugador
    if (destino->getColor() == jugador1.getColor()) {
        jugador1.incrementarCasillas();
    } else if (destino->getColor() == jugador2.getColor()) {
        jugador2.incrementarCasillas();
    }

    destino->setColor(jugador.getColor());
    jugador.incrementarCasillas();
    cout << "Casilla pintada correctamente.\n";
    return true;
}

// Obtiene la casilla adyacente en la dirección especificada
Casilla* Sistema::obtenerCasillaEnDireccion(Jugador& jugador, char dir) {
    int filaJugador = -1;
    int colJugador = -1;

    // Buscar la posicion actual del jugador en el tablero
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

    // Calcular la direccion
    int nuevaFila = filaJugador;
    int nuevaCol = colJugador;

    switch (dir) {
        case 'U': nuevaFila -= 1; break;
        case 'D': nuevaFila += 1; break;
        case 'L': nuevaCol -= 1; break;
        case 'R': nuevaCol += 1; break;
        default: return nullptr;
    }

    // Validar limites del tablero
    if (nuevaFila >= 0 && nuevaFila < 5 && nuevaCol >= 0 && nuevaCol < 5) {
        return &tablero[nuevaFila][nuevaCol];
    }

    return nullptr;  // Dirección fuera de los limites
}

// Verifica si el juego ha terminado
bool Sistema::juegoTerminado() const {
    return turnoActual > maxTurnos;
}

// Obtiene el color de una casilla específica
char Sistema::obtenerColorCasilla(int fila, int col) const {
    Jugador* jugador = tablero[fila][col].getJugador();
    if (jugador != nullptr) {
        // Devuelve la primera letra del color del jugador (ejemplo: 'r' o 'a')
        string colorJugador = jugador->getColor();
        if (!colorJugador.empty())
            return colorJugador[0];
    }
    // Si no hay jugador, devolver la primera letra del color de la casilla
    string color = tablero[fila][col].getColor();
    if (!color.empty())
        return color[0];

    return ' ';  // Casilla sin color ni jugador
}

// Ejecuta el turno de la IA
void Sistema::ejecutarTurnoIA(Jugador& jugador) {
    cout << "\nTurno IA (" << jugador.getNombre() << ")" << endl;

    // Aplicar penalización si corresponde
    if (jugador.getPenalizaciones() > 0) {
        cout << jugador.getNombre() << " tiene una penalizacion y pierde 1 accion este turno.\n";
        jugador.setAcciones(1);
        jugador.setPenalizaciones(0);
    } else {
        jugador.setAcciones(2);
    }

    while (jugador.getAcciones() > 0) {
        // Convertir el tablero actual a formato para la IA
        int tableroIA[NUM_FILAS][NUM_COLUMNAS];
        for (int i = 0; i < NUM_FILAS; ++i) {
            for (int j = 0; j < NUM_COLUMNAS; ++j) {
                Jugador* jugadorEnCasilla = tablero[i][j].getJugador();
                if (jugadorEnCasilla == &jugador1) {
                    tableroIA[i][j] = 1;
                } else if (jugadorEnCasilla == &jugador2) {
                    tableroIA[i][j] = 2;
                } else {
                    string color = tablero[i][j].getColor();
                    if (color == jugador1.getColor()) {
                        tableroIA[i][j] = 1;
                    } else if (color == jugador2.getColor()) {
                        tableroIA[i][j] = 2;
                    } else {
                        tableroIA[i][j] = 0;
                    }
                }
            }
        }

        // Obtener el mejor movimiento usando minimax
        int jugadorId = (&jugador == &jugador1) ? 1 : 2;
        Movimiento mejorMov = ia.obtener_mejor_movimiento(tableroIA, jugadorId);

        if (mejorMov.fila == -1 || mejorMov.columna == -1) {
            cout << "No hay movimientos validos disponibles.\n";
            break;
        }

        // Encontrar la casilla actual del jugador
        Casilla* casillaActual = nullptr;
        int filaActual = -1, colActual = -1;
        
        for (int i = 0; i < 5; ++i) {
            for (int j = 0; j < 5; ++j) {
                if (tablero[i][j].getJugador() == &jugador) {
                    casillaActual = &tablero[i][j];
                    filaActual = i;
                    colActual = j;
                    break;
                }
            }
            if (casillaActual) break;
        }

        if (!casillaActual) {
            cout << "Error: IA no encontrada en el tablero.\n";
            break;
        }

        bool accionRealizada = false;

        // Calcular la dirección hacia la casilla objetivo
        int difFila = mejorMov.fila - filaActual;
        int difCol = mejorMov.columna - colActual;
        char dir = ' ';

        // Determinar la dirección principal
        if (abs(difFila) > abs(difCol)) {
            dir = (difFila > 0) ? 'D' : 'U';
        } else {
            dir = (difCol > 0) ? 'R' : 'L';
        }

        // Intentar realizar la acción
        if (mejorMov.es_pintura) {
            if (pintarCasilla(jugador, dir)) {
                cout << "IA pinto una casilla.\n";
                // Verificar si se pintó a un jugador
                Casilla* casillaPintada = obtenerCasillaEnDireccion(jugador, dir);
                if (casillaPintada != nullptr) {
                    Jugador* jugadorEnCasilla = casillaPintada->getJugador();
                    if (jugadorEnCasilla != nullptr && jugadorEnCasilla != &jugador) {
                        jugadorEnCasilla->incrementarPenalizaciones(1);
                        cout << "El rival " << jugadorEnCasilla->getNombre()
                             << " fue pintado en su casilla! Pierde 1 accion en su proximo turno.\n";
                    }
                }
                accionRealizada = true;
            } else {
                // Si falla, intentar otras direcciones
                const char direcciones[] = {'U', 'D', 'L', 'R'};
                for (char dirAlt : direcciones) {
                    if (dirAlt != dir && pintarCasilla(jugador, dirAlt)) {
                        cout << "IA pinto una casilla en direccion alternativa.\n";
                        // Verificar si se pintó a un jugador
                        Casilla* casillaPintada = obtenerCasillaEnDireccion(jugador, dirAlt);
                        if (casillaPintada != nullptr) {
                            Jugador* jugadorEnCasilla = casillaPintada->getJugador();
                            if (jugadorEnCasilla != nullptr && jugadorEnCasilla != &jugador) {
                                jugadorEnCasilla->incrementarPenalizaciones(1);
                                cout << "El rival " << jugadorEnCasilla->getNombre()
                                     << " fue pintado en su casilla! Pierde 1 accion en su proximo turno.\n";
                            }
                        }
                        accionRealizada = true;
                        break;
                    }
                }
            }
        } else {
            if (moverJugador(jugador, dir)) {
                cout << "IA se movio.\n";
                accionRealizada = true;
            } else {
                // Si falla, intentar otras direcciones
                const char direcciones[] = {'U', 'D', 'L', 'R'};
                for (char dirAlt : direcciones) {
                    if (dirAlt != dir && moverJugador(jugador, dirAlt)) {
                        cout << "IA se movio en direccion alternativa.\n";
                        accionRealizada = true;
                        break;
                    }
                }
            }
        }

        if (accionRealizada) {
            jugador.setAcciones(jugador.getAcciones() - 1);
            cout << "Acciones restantes: " << jugador.getAcciones() << endl;
        } else {
            cout << "No se pudo realizar ninguna accion.\n";
            break;
        }
    }
}
