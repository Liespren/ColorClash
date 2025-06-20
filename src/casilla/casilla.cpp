/*
 * CASILLA.CPP - IMPLEMENTACIÓN DE CASILLAS DEL TABLERO
 * 
 * DESCRIPCIÓN:
 * Implementación de la clase Casilla que representa cada posición
 * del tablero de juego con su estado y conexiones.
 * 
 * FUNCIONALIDADES PRINCIPALES:
 * - Inicialización de casillas con diferentes estados
 * - Gestión de colores y jugadores en casillas
 * - Sistema de punteros para navegación eficiente
 * - Identificación de jugadores para algoritmos de IA
 * 
 */

#include "casilla.h"

// Constructor por defecto: casilla vacía sin color ni jugador
Casilla::Casilla()
    : color(""), jugador(nullptr), ptrU(nullptr), ptrD(nullptr), ptrL(nullptr), ptrR(nullptr) {}

// Constructor con parámetros: inicializa casilla con color y jugador específicos
Casilla::Casilla(const string& color, Jugador* jugador)
    : color(color), jugador(jugador), ptrU(nullptr), ptrD(nullptr), ptrL(nullptr), ptrR(nullptr) {}

// SETTERS - Métodos para modificar el estado de la casilla

// Cambia el color de la casilla (rojo/azul/blanco)
void Casilla::setColor(const string& nuevoColor) { 
    color = nuevoColor; 
}

// Asigna un jugador a la casilla (nullptr para vaciar)
void Casilla::setJugador(Jugador* nuevoJugador) { 
    jugador = nuevoJugador; 
}

// Conecta puntero hacia la casilla superior (arriba)
void Casilla::setPtrU(Casilla* ptr) { 
    ptrU = ptr; 
}

// Conecta puntero hacia la casilla inferior (abajo)
void Casilla::setPtrD(Casilla* ptr) { 
    ptrD = ptr; 
}

// Conecta puntero hacia la casilla izquierda
void Casilla::setPtrL(Casilla* ptr) { 
    ptrL = ptr; 
}

// Conecta puntero hacia la casilla derecha
void Casilla::setPtrR(Casilla* ptr) { 
    ptrR = ptr; 
}

// GETTERS - Métodos para obtener información de la casilla

// Obtiene el color actual de la casilla
string Casilla::getColor() const { 
    return color; 
}

// Obtiene el jugador que ocupa la casilla (nullptr si está vacía)
Jugador* Casilla::getJugador() const { 
    return jugador; 
}

// Obtiene puntero hacia la casilla superior
Casilla* Casilla::getPtrU() const { 
    return ptrU; 
}

// Obtiene puntero hacia la casilla inferior
Casilla* Casilla::getPtrD() const { 
    return ptrD; 
}

// Obtiene puntero hacia la casilla izquierda
Casilla* Casilla::getPtrL() const { 
    return ptrL; 
}

// Obtiene puntero hacia la casilla derecha
Casilla* Casilla::getPtrR() const { 
    return ptrR; 
}

/* 
* MÉTODO ESPECIAL PARA LA IA
* Convierte el jugador en la casilla a un ID numérico para la IA
* Retorna: 0 (vacía), 1 (jugador1), 2 (jugador2), -1 (error)
*/
int Casilla::getJugadorId(const Jugador& jugador1, const Jugador& jugador2) const {
    if (jugador == nullptr) return 0;        // Casilla vacía
    if (jugador == &jugador1) return 1;      // Jugador 1 (Rojo)
    if (jugador == &jugador2) return 2;      // Jugador 2 (Azul)
    return -1;                               // Caso inesperado
}