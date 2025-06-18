# ColorClash

**Color Clash** es un juego por turnos de tablero donde dos jugadores (Rojo y Azul) compiten para pintar la mayor cantidad de casillas. Gana quien tenga mas casillas de su color al final del juego. 

---

## Autor

Kevin Silva  
Estudiante de Ingenieria, Universidad Catolica del Norte  
Proyecto de Estructura de Datos

---

## Como jugar

- Cada jugador tiene **2 acciones por turno**.
- Las acciones pueden ser:
  - **Mover**: hacia una direccion (arriba, abajo, izquierda, derecha).
  - **Pintar**: una casilla adyacente (arriba, abajo, izquierda, derecha).
- Si pintas la casilla donde esta el otro jugador, **le quitas una accion en su siguiente turno**. Esta penalizacion solo puede aplicarse **una vez por turno**.
- Si hay un **empate** al final del juego, se agrega **un turno adicional**.

---

## To-Do

- [ ] Implementacion grafica con SFML o SDL
- [ ] Modo un jugador con arbol de decisiones
- [ ] Personalizacion de tablero (nombre_jugador, tamano, colores, cantidad_turnos)
- [ ] Ver historial de jugadas previas

---

## 📦 Estructura del Proyecto

ColorClash/
├── main.cpp
├── README.md
├── ColorClashMain.exe
├── src/
│   ├── sistema/
│   │   ├── sistema.h
│   │   └── sistema.cpp
│   ├── casilla/
│   │   ├── casilla.h
│   │   └── casilla.cpp
│   ├── ia/
│   │   ├── ia.h
│   │   └── ia.cpp
│   └── jugador/
│       ├── jugador.h
│       └── jugador.cpp

---

## Compilacion

g++ -o ColorClash.exe main.cpp src/sistema/sistema.cpp src/jugador/jugador.cpp src/casilla/casilla.cpp src/ia/ia.cpp -std=c++11

---

## 📚 Documentacion de Clases y Metodos

### Clase 'Sistema'
**Descripcion:** Controla el flujo principal del juego, el tablero, los turnos y la interaccion entre jugadores y la IA.

**Metodos principales:**
- 'iniciarJuego()': Inicializa e imprime el estado inicial del tablero.
- 'ejecutarTurno()': Ejecuta un turno completo para ambos jugadores.
- 'ejecutarAccionesJugador(Jugador&)': Gestiona las acciones del jugador humano.
- 'ejecutarTurnoIA(Jugador&)': Gestiona las acciones de la IA.
- 'imprimirEstadoTablero()': Muestra el tablero y los puntajes.
- 'moverJugador(Jugador&, char dir)': Mueve un jugador en la direccion indicada.
- 'pintarCasilla(Jugador&, char dir)': Pinta una casilla adyacente en la direccion indicada.
- 'obtenerCasillaEnDireccion(Jugador&, char dir)': Devuelve la casilla adyacente en la direccion indicada.
- 'juegoTerminado() const': Indica si el juego ha terminado.

---

### Clase 'Jugador'
**Descripcion:** Representa a un jugador, ya sea humano o IA.

**Atributos principales:** nombre, color, casillas controladas, acciones, penalizaciones.

**Metodos principales:**
- 'getNombre() const': Devuelve el nombre del jugador.
- 'getColor() const': Devuelve el color del jugador.
- 'getCasillasControladas() const': Devuelve la cantidad de casillas controladas.
- 'getAcciones() const': Devuelve el numero de acciones disponibles.
- 'setNombre(const string&)': Cambia el nombre.
- 'setColor(const string&)': Cambia el color.
- 'incrementarCasillas()': Incrementa el contador de casillas controladas.
- 'setAcciones(int)': Establece el numero de acciones.
- 'getPenalizaciones() const': Devuelve el numero de penalizaciones.
- 'setPenalizaciones(int)': Establece el numero de penalizaciones.
- 'incrementarPenalizaciones(int)': Incrementa las penalizaciones.

---

### Clase 'Casilla'
**Descripcion:** Representa una casilla del tablero, su color y el jugador que la ocupa.

**Atributos principales:** color, puntero a jugador, punteros a casillas adyacentes.

**Metodos principales:**
- 'setColor(const string&)': Cambia el color de la casilla.
- 'setJugador(Jugador*)': Asigna un jugador a la casilla.
- 'setPtrU/D/L/R(Casilla*)': Asigna punteros a las casillas adyacentes (arriba, abajo, izquierda, derecha).
- 'getColor() const': Devuelve el color de la casilla.
- 'getJugador() const': Devuelve el puntero al jugador en la casilla.
- 'getPtrU/D/L/R() const': Devuelve los punteros a las casillas adyacentes.
- 'getJugadorId(const Jugador&, const Jugador&) const': Devuelve el ID del jugador en la casilla.

---

### Clase 'IA'
**Descripcion:** Implementa la inteligencia artificial del juego, usando minimax para decidir movimientos.

**Metodos principales:**
- 'IA(int profundidad_maxima)': Constructor, define la profundidad de busqueda.
- 'Movimiento obtener_mejor_movimiento(int tablero[5][5], int jugador)': Calcula el mejor movimiento posible para la IA.
- 'int minimax(Estado, int, int, int, bool)': Algoritmo de busqueda minimax con poda alfa-beta.
- 'vector<Movimiento> generar_movimientos_validos(const Estado&)': Genera todos los movimientos validos desde un estado.
- 'Estado aplicar_movimiento(const Estado&, const Movimiento&)': Aplica un movimiento y devuelve el nuevo estado.
- 'int evaluar(const Estado&)': Evalua el estado del tablero para la IA.
- 'bool es_movimiento_valido(const Estado&, const Movimiento&) const': Verifica si un movimiento es valido.
- 'int evaluar_posicion_estrategica(int, int) const': Evalua el valor estrategico de una posicion.

---

### Estructuras auxiliares

- **'struct Movimiento'**  
  Representa un movimiento o accion de pintar.  
  - 'int fila, columna': Coordenadas del movimiento.
  - 'bool es_pintura': Indica si es una accion de pintar.

- **'struct Estado'**  
  Representa el estado del tablero y el jugador actual.  
  - 'int tablero[5][5]': Estado del tablero.
  - 'int jugador_actual': Jugador que tiene el turno.