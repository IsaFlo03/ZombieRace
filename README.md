# 🧟 Zombie Mayhem

## 🎯 Objetivo del Juego
Sobrevivir al apocalipsis zombie, atravesando un campo lleno de zombies hasta llegar a un lugar seguro. Los jugadores pueden elegir entre dos personajes (Hello Kitty o Snoopy) y superar múltiples niveles evitando enemigos zombies para alcanzar la cabaña de refugio.

## 🎮 Controles
- **Flechas Izquierda/Derecha**: Movimiento horizontal del personaje
- **Barra Espaciadora (Space)**: Saltar
- **Mouse**: Interactuar con menús y botones

## 🎲 Mecánicas Principales

### Sistema de Movimiento
- **Desplazamiento lateral**: Los personajes se mueven horizontalmente con física de aceleración
- **Sistema de salto**: Mecánica de salto con gravedad realista y detección de colisión con el suelo
- **Parallax scrolling**: Efecto de fondo infinito con múltiples capas que simulan profundidad

### Sistema de Colisiones
- **Detección precisa**: Hitboxes reducidos (40% del tamaño del sprite) para colisiones más justas
- **Colisión con enemigos**: Contacto con zombies resulta en derrota instantánea
- **Sistema de victoria**: Alcanzar la meta (cabaña) completa el nivel exitosamente

### Sistema de Enemigos
- **8 Tipos de Zombies**: Zombirron, Zombiano, Zombilia, Zombando, Zombiguada, Zombiscocho, Zombiela, Zombiboy
- **Posicionamiento estratégico**: Zombies distribuidos en posiciones fijas a lo largo del recorrido
- **Tamaños variables**: Cada zombie tiene características visuales únicas, con Zombiboy siendo más grande

### Mecánica de Niveles
- **Nivel 1 (Snoopy)**: Recorrido con fondos alternados y meta en cabaña abierta
- **Nivel 2 (Hello Kitty)**: Desafío similar con enemigos zombies distribuidos
- **Múltiples niveles**: Sistema extensible con nivel 2 y nivel 3 implementados

### Sistema de Derrota/Victoria
- **Pantalla de derrota**: Sprite especial del personaje perdedor con opción de reinicio
- **Pantalla de victoria**: Interior de la cabaña con mensaje de éxito
- **Sistema de reinicio**: Click del mouse en botón "Reiniciar" para volver a intentar

## ✨ Características

### 🎨 Visual
- **Sprites animados**: Sistema de animación por frames para personajes
- **Gráficos personalizados**: Assets únicos para cada personaje y zombie
- **Efectos visuales**: Transiciones suaves entre estados del juego
- **UI temática**: Menú principal con fuente zombie personalizada
- **Fondos dinámicos**: Múltiples fondos con efecto parallax para sensación de movimiento

### 🎵 Audio
- **Sistema de audio SFML**: Preparado para música de fondo y efectos de sonido
- **Assets de música**: Directorio dedicado para archivos de audio

### 🎯 Gameplay
- **Sistema de selección de personaje**: Elige entre Hello Kitty y Snoopy
- **Zombiepedia**: Enciclopedia interactiva con información de los 8 tipos de zombies
- **Progresión por niveles**: Sistema de niveles con dificultad incremental
- **Reinicio rápido**: Funcionalidad de reintentar nivel tras derrota
- **Distancia medida**: Sistema de tracking de progreso del jugador

### 🧩 Extras
- **Menú interactivo**: Sistema completo de navegación entre menús

## 👥 Equipo
- **Líder**: Isabel Guadalupe Flores Salas (@IsaFlo03-github)
- **Integrante 2**: Gabriela Paola Cardona Muñoz (@Gabrielobsky-github)

## 🛠️ Tecnologías

### Motor/Framework
- **SFML (Simple and Fast Multimedia Library)**: Framework principal para gráficos 2D, manejo de ventanas, eventos y audio

### Lenguaje
- **C++**: Lenguaje de programación principal del proyecto
- **Estándar**: C++11 o superior

### Librerías
- **SFML Graphics**: Renderizado de sprites, texturas y primitivas
- **SFML Window**: Gestión de ventanas y eventos
- **SFML System**: Funcionalidades del sistema (Clock, Vector2)
- **SFML Audio**: Sistema de sonido y música

### Herramientas de Desarrollo
- **Compilador**: g++ (GNU C++ Compiler)
- **Sistema de Build**: GNU Make con makefiles personalizados
- **Control de Versiones**: Git/GitHub

### Assets
- **Fuentes personalizadas**: Zombie Hunger font para UI temática
- **Imágenes**: Sprites PNG para personajes, enemigos, fondos y UI
- **Estructura organizada**: 
  - `assets/fonts/`: Archivos de fuentes
  - `assets/images/`: Sprites y texturas
  - `assets/music/`: Archivos de audio

## 📁 Estructura del Proyecto
```
ZombieRace/
├── src/              # Código fuente (.cpp)
├── include/          # Headers (.hpp)
├── bin/              # Ejecutables compilados
├── assets/           # Recursos del juego
│   ├── fonts/        # Fuentes
│   ├── images/       # Sprites y texturas
│   └── music/        # Audio
├── docs/             # Documentación
└── makefile          # Sistema de compilación
```

## 🎮 Características Técnicas

### Sistema de Animación
- **Frame-based animation**: Sistema de animación por cuadros
- **Timing preciso**: Control de velocidad de animación con sf::Clock
- **Sprite sheets**: Texturas divididas en frames para animaciones fluidas

### Sistema de Renderizado
- **Ventana de 800x600**: Resolución estándar del juego
- **Escalado inteligente**: Sistema de escala proporcional para diferentes tamaños de assets
- **Capas de renderizado**: Orden correcto de dibujo (fondo → enemigos → jugador → UI)

### Gestión de Memoria
- **Texturas cargadas eficientemente**: Sin duplicación innecesaria
- **Cleanup apropiado**: Liberación de recursos al cerrar

## 🎯 Modos de Juego

### Modo Historia
- Recorrido completo por los niveles con los personajes principales
- Sistema de progresión lineal

### Zombiepedia
- Galería interactiva de zombies
- Sistema de páginas navegable
- Información detallada de cada tipo de zombie


## 📄 Licencia
Ver archivo LICENSE para detalles

## 🙏 Créditos
- **Assets originales**: Creados por el equipo de desarrollo
- **SFML**: Laurent Gomila y colaboradores
- **Fuente Zombie Hunger**: Font utilizada para la temática zombie
- **Imagenes de Snoopy y Hello Kitty**: Fanarts