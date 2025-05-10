#pragma once

#include <iostream>
using namespace std;

class Sistema {

private:
    //Jugador jugador;
    int turnoActual;
    int maxTurnos;
    
public:
    Sistema();
    void imprimirIniciarSistema();
    void iniciarJuego();
    void ejecutarTurno();
    bool juegoTerminado() const;
};
