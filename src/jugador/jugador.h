#pragma once
#include <string>

using std::string;

class Jugador {
private:
    string nombre;
    string color;
    int casillasControladas;

public:
    Jugador();
    Jugador(const string& nombre, const string& color);

    string getNombre() const;
    string getColor() const;
    int getCasillasControladas() const;

    void setNombre(const string& nuevoNombre);
    void setColor(const string& nuevoColor);
    void incrementarCasillas();
};
