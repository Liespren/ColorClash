#include "src/sistema/sistema.h"

int main() {
    Sistema juego;
    juego.iniciarJuego();

    while (!juego.juegoTerminado()) {
        juego.ejecutarTurno();
    }

    return 0;
}
