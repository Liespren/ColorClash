#pragma once
#include <string>

using std::string;

class Jugador {
private:
    string nombre;
    string color;
    int casillasControladas;
    int acciones;  

public:
    Jugador();
    Jugador(const string& nombre, const string& color);

    string getNombre() const;
    string getColor() const;
    int getCasillasControladas() const;
    int getAcciones() const; 

    void setNombre(const string& nuevoNombre);
    void setColor(const string& nuevoColor);
    void incrementarCasillas();

    void setAcciones(int nuevasAcciones); 
    void usarAccion();                    
    bool tieneAcciones() const;          
};
