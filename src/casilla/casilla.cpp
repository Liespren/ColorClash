#include "casilla.h"

Casilla::Casilla() 
    : color(""), jugador(""), ptrU(nullptr), ptrD(nullptr), ptrL(nullptr), ptrR(nullptr) {}


Casilla::Casilla(const string& color, const string& jugador) 
    : color(color), jugador(jugador), ptrU(nullptr), ptrD(nullptr), ptrL(nullptr), ptrR(nullptr) {}

void Casilla::setColor(const string& nuevoColor) {color = nuevoColor;}
void Casilla::setJugador(const string& nuevoJugador) {jugador = nuevoJugador;}
void Casilla::setPtrU(Casilla* ptr) {ptrU = ptr;}
void Casilla::setPtrD(Casilla* ptr) {ptrD = ptr;}
void Casilla::setPtrL(Casilla* ptr) {ptrL = ptr;}
void Casilla::setPtrR(Casilla* ptr) {ptrR = ptr;}

string Casilla::getColor() const {return color;}
string Casilla::getJugador() const {return jugador;}
Casilla* Casilla::getPtrU() const {return ptrU;}
Casilla* Casilla::getPtrD() const {return ptrD;}
Casilla* Casilla::getPtrL() const {return ptrL;}
Casilla* Casilla::getPtrR() const {return ptrR;}