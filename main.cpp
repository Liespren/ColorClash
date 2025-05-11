#include <iostream>
#include "src/sistema/sistema.h"
#include "src/sistema/sistema.h"


using namespace std;

int main() {
    cout << "Abriendo programa" << endl;

    Sistema sistema;

    sistema.imprimirIniciarSistema();
    sistema.iniciarJuego();

    while (!sistema.juegoTerminado()) {
        sistema.ejecutarTurno();
    }

    cout << "Juego terminado." << endl;
    cout << "Cerrando programa" << endl;

    return 0;
}

