/*
 * SISTEMA.H - CONTROLADOR PRINCIPAL DEL JUEGO
 * 
 * DESCRIPCIÓN:
 * Esta clase actúa como el controlador principal del juego ColorClash.
 * Gestiona el tablero, los jugadores, los turnos y la lógica del juego.
 * 
 * FUNCIONALIDADES:
 * - Gestión del tablero 5x5 con sistema de punteros
 * - Control de turnos y acciones de jugadores
 * - Integración con la IA para el jugador computacional
 * - Visualización del estado del juego con colores
 * - Validación de movimientos y pintura
 * 
 */

#pragma once

#include "../casilla/casilla.h"
#include "../jugador/jugador.h"
#include "../ia/ia.h"
#include <iostream>

class Sistema {
private:
    Casilla tablero[5][5];    // Tablero del juego con sistema de punteros
    int turnoActual;          // Número del turno actual
    int maxTurnos;            // Número máximo de turnos (5 por defecto)
    Jugador jugador1;         // Jugador humano (Rojo)
    Jugador jugador2;         // Jugador IA (Azul)
    IA ia;                    // Inteligencia artificial

public:
    // Constructor: inicializa el tablero y conecta punteros
    Sistema();

    // Habilita colores ANSI para Windows
    void habilitarColoresANSI();

    // Inicia el juego e imprime el estado inicial
    void iniciarJuego();
    
    // Ejecuta un turno completo (jugador humano + IA)
    void ejecutarTurno();
    
    // Gestiona las acciones del jugador humano
    void ejecutarAccionesJugador(Jugador& jugador);
    
    // Imprime el estado actual del tablero con colores
    void imprimirEstadoTablero();
    
    // Mueve un jugador en la dirección especificada
    bool moverJugador(Jugador& jugador, char dir);
    
    // Pinta una casilla adyacente en la dirección especificada
    bool pintarCasilla(Jugador& jugador, char dir);

    // Obtiene la casilla adyacente en la dirección especificada
    Casilla* obtenerCasillaEnDireccion(Jugador& jugador, char dir);
    
    // Obtiene el color de una casilla específica
    char obtenerColorCasilla(int fila, int col) const;

    // Ejecuta el turno de la IA
    void ejecutarTurnoIA(Jugador& jugador);

    // Verifica si el juego ha terminado
    bool juegoTerminado() const;
};
