/*
 * JUGADOR.CPP - IMPLEMENTACIÓN DE LA GESTIÓN DE JUGADORES
 * 
 * DESCRIPCIÓN:
 * Implementación de la clase Jugador que maneja el estado y comportamiento
 * de cada jugador en el juego ColorClash.
 * 
 * FUNCIONALIDADES PRINCIPALES:
 * - Inicialización de jugadores con diferentes configuraciones
 * - Gestión de puntuación y casillas controladas
 * - Control de acciones disponibles por turno
 * - Sistema de penalizaciones para balance del juego
 * 
 */

#include "jugador.h"

// Constructor por defecto: crea un jugador sin nombre con color blanco
Jugador::Jugador() : nombre(""), color("blanco"), casillasControladas(0), acciones(2) {}

// Constructor con parámetros: inicializa jugador con nombre y color específicos
Jugador::Jugador(const string& nombre, const string& color)
    : nombre(nombre), color(color), casillasControladas(0), acciones(2) {}

// GETTERS - Métodos para obtener información del jugador

// Obtiene el nombre o identificador del jugador
string Jugador::getNombre() const {
    return nombre;
}

// Obtiene el color asignado al jugador (rojo/azul)
string Jugador::getColor() const {
    return color;
}

// Obtiene el número de casillas que controla (puntuación actual)
int Jugador::getCasillasControladas() const {
    return casillasControladas;
}

// Obtiene las acciones disponibles en el turno actual
int Jugador::getAcciones() const {
    return acciones;
}

// Obtiene el número de penalizaciones pendientes
int Jugador::getPenalizaciones() const {
    return penalizaciones;
}

// SETTERS - Métodos para modificar información del jugador

// Cambia el nombre del jugador
void Jugador::setNombre(const string& nuevoNombre) {
    nombre = nuevoNombre;
}

// Cambia el color del jugador
void Jugador::setColor(const string& nuevoColor) {
    color = nuevoColor;
}

// Establece el número de acciones disponibles para el turno
void Jugador::setAcciones(int nuevasAcciones) {
    acciones = nuevasAcciones;
}

// Establece el número de penalizaciones pendientes
void Jugador::setPenalizaciones(int p) {
    penalizaciones = p;
}

// MÉTODOS DE MODIFICACIÓN DE ESTADO

// Incrementa el contador de casillas controladas (puntuación)
void Jugador::incrementarCasillas() {
    ++casillasControladas;
}

// Añade penalizaciones al jugador (por defecto 1)
void Jugador::incrementarPenalizaciones(int p) {
    penalizaciones += p;
}
