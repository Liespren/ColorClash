#pragma once
#include <string>
using namespace std;

class Casilla {
private:
    string color;
    string jugador;

    Casilla* ptrU;
    Casilla* ptrD;
    Casilla* ptrL;
    Casilla* ptrR;

public:
    Casilla();
    Casilla(const string& color, const string& jugador);

        void setColor(const string& nuevoColor);
    void setJugador(const string& nuevoJugador);
    void setPtrU(Casilla* ptr);
    void setPtrD(Casilla* ptr);
    void setPtrL(Casilla* ptr);
    void setPtrR(Casilla* ptr);
    
    string getColor() const;
    string getJugador() const;
    Casilla* getPtrU() const;
    Casilla* getPtrD() const;
    Casilla* getPtrL() const;
    Casilla* getPtrR() const;
};
