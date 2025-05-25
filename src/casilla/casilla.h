#pragma once
#include <string>
#include "../jugador/jugador.h"  // Incluye la definición de Jugador

using std::string;

class Casilla {
private:
    string color;
    Jugador* jugador;   // Puntero a jugador en vez de string
    Casilla* ptrU;
    Casilla* ptrD;
    Casilla* ptrL;
    Casilla* ptrR;

public:
    Casilla();
    Casilla(const string& color, Jugador* jugador);  // Cambia el parámetro

    void setColor(const string& nuevoColor);
    void setJugador(Jugador* nuevoJugador);  // Cambia el tipo
    void setPtrU(Casilla* ptr);
    void setPtrD(Casilla* ptr);
    void setPtrL(Casilla* ptr);
    void setPtrR(Casilla* ptr);

    string getColor() const;
    Jugador* getJugador() const;  // Devuelve puntero a jugador

    Casilla* getPtrU() const;
    Casilla* getPtrD() const;
    Casilla* getPtrL() const;
    Casilla* getPtrR() const;
};
