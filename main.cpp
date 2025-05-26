#include <iostream>
#include <string>
#include <limits>
#include "src/sistema/sistema.h"

using namespace std;

int main() {
    string opcion;

    while (true) {
        cout << "\nColor Clash Menu" << endl;
        cout << "1) Iniciar Juego" << endl;
        cout << "2) Salir" << endl;
        cout << "Selecciona una opcion: ";
        getline(cin, opcion); // Usamos getline para evitar problemas con \n

        if (opcion == "1") {
            Sistema juego;
            juego.iniciarJuego();

            while (!juego.juegoTerminado()) {
                juego.ejecutarTurno();
            }

            // Limpiar cualquier enter pendiente del flujo después del juego
            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        } else if (opcion == "2") {
            cout << "Saliendo del juego. Hasta luego.\n";
            break;

        } else {
            cout << "Opcion invalida. Intenta nuevamente." << endl;
        }
    }

    return 0;
}
