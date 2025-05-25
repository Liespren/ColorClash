#include "jugador.h"

Jugador::Jugador() : nombre(""), color(""), casillasControladas(0) {}

Jugador::Jugador(const string& nombre, const string& color)
    : nombre(nombre), color(color), casillasControladas(0) {}

string Jugador::getNombre() const {
    return nombre;
}

string Jugador::getColor() const {
    return color;
}

int Jugador::getCasillasControladas() const {
    return casillasControladas;
}

void Jugador::setNombre(const string& nuevoNombre) {
    nombre = nuevoNombre;
}

void Jugador::setColor(const string& nuevoColor) {
    color = nuevoColor;
}

void Jugador::incrementarCasillas() {
    casillasControladas++;
}
