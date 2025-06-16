#include "jugador.h"

Jugador::Jugador() : nombre(""), color("blanco"), casillasControladas(0), acciones(2) {}

Jugador::Jugador(const string& nombre, const string& color)
    : nombre(nombre), color(color), casillasControladas(0), acciones(2) {}

string Jugador::getNombre() const {
    return nombre;
}

string Jugador::getColor() const {
    return color;
}

int Jugador::getCasillasControladas() const {
    return casillasControladas;
}

int Jugador::getAcciones() const {
    return acciones;
}

void Jugador::setNombre(const string& nuevoNombre) {
    nombre = nuevoNombre;
}

void Jugador::setColor(const string& nuevoColor) {
    color = nuevoColor;
}

void Jugador::incrementarCasillas() {
    ++casillasControladas;
}

void Jugador::setAcciones(int nuevasAcciones) {
    acciones = nuevasAcciones;
}

int Jugador::getPenalizaciones() const {
    return penalizaciones;
}

void Jugador::setPenalizaciones(int p) {
    penalizaciones = p;
}

void Jugador::incrementarPenalizaciones(int p) {
    penalizaciones += p;
}