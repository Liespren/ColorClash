# ColorClash

**Color Clash** es un juego por turnos de tablero donde dos jugadores (Rojo y Azul) compiten para pintar la mayor cantidad de casillas. Gana quien tenga mas casillas de su color al final del juego. 

---

## Autor

Kevin Silva Ossandón
Estudiante de Ingeniería en Tecnolgías de Información, Universidad Católica del Norte  
Proyecto de Estructura de Datos

---

## Como jugar

- Cada jugador tiene **2 acciones por turno**.
- Las acciones pueden ser:
  - **Mover**: hacia una direccion (arriba, abajo, izquierda, derecha).
  - **Pintar**: una casilla adyacente (arriba, abajo, izquierda, derecha).
- Si pintas la casilla donde esta el otro jugador, **le quitas una accion en su siguiente turno**.
- Si hay un **empate** al final del juego, se agrega **un turno adicional**.

---

## Compilación y Ejecución

### Compilar
```bash
g++ -o ColorClash.exe main.cpp src/sistema/sistema.cpp src/jugador/jugador.cpp src/casilla/casilla.cpp src/ia/ia.cpp -std=c++11
```

### Ejecutar
```bash
./ColorClash.exe
```

---

## Estructura del Proyecto

```
ColorClash/
├── main.cpp              # Punto de entrada del programa
├── src/
│   ├── sistema/          # Lógica principal del juego
│   ├── jugador/          # Clase Jugador
│   ├── casilla/          # Clase Casilla del tablero
│   └── ia/               # Inteligencia artificial (minimax)
```

---

## Características

- **Juego por turnos** con 2 jugadores
- **IA inteligente** usando algoritmo minimax con poda alfa-beta
- **Sistema de penalizaciones** por pintar al oponente
- **Tablero 5x5** con navegación eficiente usando punteros
- **Interfaz de consola** clara y fácil de usar

---

## Documentación

La documentación técnica detallada está disponible en el archivo PDF adjunto, que incluye:
- Arquitectura del sistema
- Documentación completa de clases y métodos
- Algoritmos de IA
- Análisis de rendimiento

---