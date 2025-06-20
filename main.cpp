/*
 * ============================================================================
 * COLORCLASH - PUNTO DE ENTRADA PRINCIPAL
 * ============================================================================
 * 
 * DESCRIPCIÓN:
 * Este archivo contiene la función main() que sirve como punto de entrada
 * principal del juego ColorClash. Gestiona el menú principal y el flujo
 * básico de la aplicación.
 * 
 * FUNCIONALIDADES:
 * - Menú principal con opciones de juego
 * - Inicialización del sistema de juego
 * - Bucle principal del juego
 * - Gestión de entrada/salida del usuario
 * 
 * AUTOR: Kevin Silva
 * ASIGNATURA: Estructura de Datos
 * ============================================================================
 */

#include <iostream>
#include <string>
#include <limits>
#include "src/sistema/sistema.h"

using namespace std;

int main() {
    string opcion;

    // Bucle principal del menú
    while (true) {
        // Mostrar opciones del menú
        cout << "\nColor Clash Menu" << endl;
        cout << "1) Iniciar Juego" << endl;
        cout << "2) Salir" << endl;
        cout << "Selecciona una opcion: ";
        getline(cin, opcion); // Usamos getline para evitar problemas con \n

        if (opcion == "1") {
            // Crear instancia del sistema de juego
            Sistema juego;
            juego.iniciarJuego();

            // Bucle principal del juego - ejecuta turnos hasta que termine
            while (!juego.juegoTerminado()) {
                juego.ejecutarTurno();
            }

            // Limpiar cualquier enter pendiente del flujo despues del juego
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

        } else if (opcion == "2") {
            // Salir del programa
            cout << "Saliendo del juego. Hasta luego.\n";
            break;

        } else {
            // Opción inválida
            cout << "Opcion invalida. Intenta nuevamente." << endl;
        }
    }

    return 0;
}
