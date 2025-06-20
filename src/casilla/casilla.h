/*
 * CASILLA.H - REPRESENTACIÓN DE CASILLAS DEL TABLERO
 * 
 * DESCRIPCIÓN:
 * Esta clase representa una casilla individual del tablero de juego.
 * Cada casilla tiene un color, puede contener un jugador y mantiene
 * punteros a las casillas adyacentes para navegación eficiente.
 * 
 * FUNCIONALIDADES:
 * - Gestión del color de la casilla
 * - Almacenamiento de jugadores en la casilla
 * - Sistema de punteros para navegación adyacente
 * - Identificación de jugadores para la IA
 * 
 */

#pragma once
#include <string>
#include "../jugador/jugador.h" 

using std::string;

class Casilla {
private:
    string color;           // Color actual de la casilla (rojo/azul/blanco)
    Jugador* jugador;       // Puntero al jugador que ocupa la casilla (nullptr si está vacía)
    Casilla* ptrU;          // Puntero a la casilla superior (arriba)
    Casilla* ptrD;          // Puntero a la casilla inferior (abajo)
    Casilla* ptrL;          // Puntero a la casilla izquierda
    Casilla* ptrR;          // Puntero a la casilla derecha

public:
    // Constructor por defecto: casilla sin color ni jugador
    Casilla();
    
    // Constructor con parámetros: casilla con color y jugador específicos
    Casilla(const string& color, Jugador* jugador);

    // SETTERS - Métodos para modificar el estado de la casilla
    void setColor(const string& nuevoColor);        // Cambia el color de la casilla
    void setJugador(Jugador* nuevoJugador);         // Asigna un jugador a la casilla
    void setPtrU(Casilla* ptr);                     // Conecta puntero hacia arriba
    void setPtrD(Casilla* ptr);                     // Conecta puntero hacia abajo
    void setPtrL(Casilla* ptr);                     // Conecta puntero hacia izquierda
    void setPtrR(Casilla* ptr);                     // Conecta puntero hacia derecha

    // GETTERS - Métodos para obtener información de la casilla
    string getColor() const;                        // Obtiene el color de la casilla
    Jugador* getJugador() const;                    // Obtiene el jugador en la casilla
    Casilla* getPtrU() const;                       // Obtiene puntero hacia arriba
    Casilla* getPtrD() const;                       // Obtiene puntero hacia abajo
    Casilla* getPtrL() const;                       // Obtiene puntero hacia izquierda
    Casilla* getPtrR() const;                       // Obtiene puntero hacia derecha

    // Método especial para la IA: obtiene ID numérico del jugador
    int getJugadorId(const Jugador& jugador1, const Jugador& jugador2) const;
    /*
    * La IA genera múltiples estados del tablero durante la búsqueda
    * Necesita copiar y modificar estados rápidamente
    * Los números son más fáciles de copiar que objetos
    */
};
