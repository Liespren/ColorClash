/*
 * JUGADOR.H - GESTIÓN DE JUGADORES
 * 
 * DESCRIPCIÓN:
 * Esta clase representa a un jugador en el juego ColorClash, ya sea humano o IA.
 * Gestiona el estado del jugador incluyendo su identificación, puntuación,
 * acciones disponibles y penalizaciones.
 * 
 * FUNCIONALIDADES:
 * - Gestión de identidad del jugador (nombre y color)
 * - Control de casillas controladas (puntuación)
 * - Gestión de acciones por turno
 * - Sistema de penalizaciones
 * 
 */

#pragma once
#include <string>

using std::string;

class Jugador {
private:
    string nombre;              // Nombre o identificador del jugador
    string color;               // Color asignado al jugador (rojo/azul)
    int casillasControladas;    // Número de casillas que controla (puntuación)
    int acciones;               // Acciones disponibles en el turno actual
    int penalizaciones = 0;     // Penalizaciones pendientes (pierde acciones)

public:
    // Constructor por defecto: jugador sin nombre, color blanco
    Jugador();
    
    // Constructor con parámetros: nombre y color específicos
    Jugador(const string& nombre, const string& color);

    // Getters - Obtener información del jugador
    string getNombre() const;           // Obtiene el nombre del jugador
    string getColor() const;            // Obtiene el color del jugador
    int getCasillasControladas() const; // Obtiene la puntuación actual
    int getAcciones() const;            // Obtiene acciones disponibles
    int getPenalizaciones() const;      // Obtiene penalizaciones pendientes

    // Setters - Modificar información del jugador
    void setNombre(const string& nuevoNombre);     // Cambia el nombre
    void setColor(const string& nuevoColor);       // Cambia el color
    void setAcciones(int nuevasAcciones);          // Establece acciones disponibles
    void setPenalizaciones(int p);                 // Establece penalizaciones

    // Métodos de modificación de estado
    void incrementarCasillas();                    // Incrementa la puntuación
    void incrementarPenalizaciones(int p = 1);     // Añade penalizaciones
};
