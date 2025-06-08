# ColorClash

**Color Clash** es un juego por turnos de tablero donde dos jugadores (Rojo y Azul) compiten para pintar la mayor cantidad de casillas. Gana quien tenga más casillas de su color al final del juego. 

---

## Autor

Kevin Silva
Estudiante de Ingeniería, Universidad Católica del Norte
Proyecto de Estructura de Datos

---

## Cómo jugar

- Cada jugador tiene **2 acciones por turno**.
- Las acciones pueden ser:
  - **Mover**: hacia una dirección (arriba, abajo, izquierda, derecha).
  - **Pintar**: una casilla adyacente (arriba, abajo, izquierda, derecha).
- Si pintas la casilla donde está el otro jugador, **le quitas una acción en su siguiente turno**.  Esta penalización solo puede aplicarse **una vez por turno**.
- Si hay un **empate** al final del juego, se añade **un turno adicional**.

---

## To-Do

- [ ] Implementación gráfica con SFML o SDL
- [ ] Modo un jugador con arbol de decisiones
- [ ] Personalización de tablero (nombre_jugador, tamaño, colores, cantidad_turnos)
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

## Compilación

g++ -std=c++17 main.cpp src/sistema/sistema.cpp src/casilla/casilla.cpp src/jugador/jugador.cpp -o ColorClashMain.exe