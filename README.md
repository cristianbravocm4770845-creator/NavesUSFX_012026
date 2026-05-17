# NavesUSFX_012026

## Descripcion General

**NavesUSFX_012026** es un videojuego tipo **Twin Stick Shooter** desarrollado en **Unreal Engine 4** con **C++14**.

El proyecto consiste en:
- Una nave espacial controlable por el jugador
- Sistema de movimiento en 2D (vista superior)
- Sistema de disparo de proyectiles en 8 direcciones
- Fisica y colisiones integradas con el motor Unreal Engine
- Comentarios detallados en todo el codigo explicando cada clase, metodo y propiedad

## Caracteristicas del Proyecto

### Clases Principales

#### 1. **ANavesUSFX_012026Projectile** (Proyectiles/Balas)
- Representa las balas disparadas por la nave
- Utiliza `UProjectileMovementComponent` para movimiento automatico
- Velocidad constante de 3000 unidades/segundo
- Ciclo de vida de 3 segundos
- Colisiona con objetos dinamicos aplicando impulso
- **Archivos**: `NavesUSFX_012026Projectile.h/cpp`

#### 2. **ANavesUSFX_012026Pawn** (Nave del Jugador)
- Personaje controlable del jugador
- Componentes visuales: `ShipMeshComponent` (malla 3D)
- Componentes de camara: `CameraComponent` + `SpringArmComponent` (vista cenital)
- Movimiento basado en entrada del jugador (WASD)
- Sistema de disparo con temporizador (FireRate = 0.1s)
- Reproduccion de efectos de sonido al disparar
- **Archivos**: `NavesUSFX_012026Pawn.h/cpp`

#### 3. **ANavesUSFX_012026GameMode** (Reglas del Juego)
- Define las reglas generales del juego
- Asigna la clase Pawn por defecto (`ANavesUSFX_012026Pawn`)
- Punto central de configuracion de la partida
- **Archivos**: `NavesUSFX_012026GameMode.h/cpp`

### Componentes Utilizados

| Componente | Uso | Clase |
|-----------|-----|-------|
| `UStaticMeshComponent` | Renderizado 3D de malla estatica | UE4 Core |
| `UProjectileMovementComponent` | Movimiento automatico de proyectiles | UE4 GameFramework |
| `UCameraComponent` | Camara del jugador | UE4 Camera |
| `USpringArmComponent` | Boom de camara (distancia/angulo) | UE4 GameFramework |
| `UInputComponent` | Manejo de entrada del jugador | UE4 InputComponent |

### Eventos y Callbacks

- **OnComponentHit()**: Se dispara cuando un proyectil colisiona
- **ShotTimerExpired()**: Se ejecuta tras terminar el cooldown de disparo
- **Tick()**: Se ejecuta cada fotograma para actualizar entrada y movimiento

## Estructura de Directorios

```
NavesUSFX_012026/
??? Source/
?   ??? NavesUSFX_012026/
?   ?   ??? NavesUSFX_012026.cpp
?   ?   ??? NavesUSFX_012026.h
?   ?   ??? NavesUSFX_012026Projectile.cpp
?   ?   ??? NavesUSFX_012026Projectile.h
?   ?   ??? NavesUSFX_012026Pawn.cpp
?   ?   ??? NavesUSFX_012026Pawn.h
?   ?   ??? NavesUSFX_012026GameMode.cpp
?   ?   ??? NavesUSFX_012026GameMode.h
?   ??? NavesUSFX_012026.Target.cs
?   ??? NavesUSFX_012026Editor.Target.cs
??? Content/
?   ??? TwinStick/
?       ??? Meshes/
?       ??? Audio/
?       ??? Maps/
??? NavesUSFX_012026.uproject
??? .gitignore
??? .gitattributes
??? README.md (este archivo)
```

## Requisitos

- **Unreal Engine 4.x** (4.25 o superior)
- **Visual Studio 2019** o superior (para desarrollo en C++)
- **Git LFS** (para archivos grandes)

## Instalacion y Configuracion

### 1. Clonar el Repositorio

```bash
git clone https://github.com/cristianbravocm4770845-creator/NavesUSFX_012026.git
cd NavesUSFX_012026
git lfs pull
```

### 2. Generar Archivos de Proyecto (Visual Studio)

```bash
# En Windows
GenerateProjectFiles.bat

# En Linux/Mac
./GenerateProjectFiles.sh
```

### 3. Compilar el Proyecto

#### Opcion A: Visual Studio
1. Abre `NavesUSFX_012026.sln`
2. Selecciona configuracion: `Development Editor` o `Shipping`
3. Click derecho en la solucion ? Build

#### Opcion B: Unreal Editor
1. Abre `NavesUSFX_012026.uproject` con Unreal Engine 4
2. El editor compilara automaticamente los fuentes

### 4. Ejecutar el Proyecto

- **En Editor**: File ? Open Level ? Selecciona el mapa principal
- **Standalone**: Compile y ejecuta el binario generado en `Binaries/`

## Controles del Juego

| Entrada | Accion |
|---------|--------|
| **W / A / S / D** | Mover nave (arriba, izquierda, abajo, derecha) |
| **Flechas de Teclado** | Disparar proyectiles en la direccion |
| **ESC** | Salir del juego |

## Mecanicas del Juego

### Movimiento
- La nave se mueve a velocidad constante de 1000 unidades/segundo
- Movimiento limitado al plano horizontal (vista cenital)
- Colisiona con obstaculos (rebote/deslizamiento)

### Disparo
- Cooldown entre disparos: 0.1 segundos (10 disparos/segundo maximo)
- Velocidad del proyectil: 3000 unidades/segundo
- Alcance: ~9000 unidades (3 segundos de vuelo)
- Los proyectiles se destruyen al colisionar

### Fisica
- No hay gravedad (juego 2D top-down)
- Los proyectiles no rebotan
- Los objetos dinamicos reciben impulso al ser golpeados

## Documentacion del Codigo

**TODA** la logica del codigo esta comentada en detalle, incluyendo:
- Descripcion general de cada clase
- Proposito de cada componente
- Explicacion de cada metodo y propiedad
- Flujo de ejecucion paso a paso
- Parametros y valores tipicos
- Efectos en el juego

Para entender cualquier parte del codigo, lee los comentarios de bloque `/** ... */`

### Ejemplo de Comentarios

```cpp
/**
 * M ETODO: OnHit()
 * 
 * TIPO: Manejador de evento (Event handler)
 * EVENTO DISPARADOR: OnComponentHit de ProjectileMesh
 * 
 * PROP OSITO:
 * Responder cuando el proyectil colisiona con algo en el mundo.
 * Es el punto de entrada de toda la logica de impacto del proyectil.
 */
void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, 
           UPrimitiveComponent* OtherComp, FVector NormalImpulse, 
           const FHitResult& Hit);
```

## Git LFS - Archivos Grandes

Este proyecto utiliza **Git LFS** (Large File Storage) para manejar archivos grandes:

### Archivos Rastreados por LFS

- `*.uasset` - Assets de Unreal (mallas, texturas, materiales)
- `*.umap` - Mapas/Niveles
- `*.wav`, `*.mp3`, `*.ogg` - Audio
- `*.png`, `*.jpg`, `*.tga` - Imagenes
- `Binaries/**` - Archivos compilados
- `Intermediate/**` - Cache del editor

### Archivos en Git Normal

- `*.cpp`, `*.h` - Codigo fuente (versionado linea por linea)
- `*.uproject` - Configuracion del proyecto
- `*.md`, `*.txt` - Documentacion

## Estructura de Clases (Jerarquia)

```
AActor (Unreal Base)
  ??? ANavesUSFX_012026Projectile
  ?   ??? Responsabilidad: Movimiento y colision de proyectiles
  ?
  ??? APawn (Unreal Base)
  ?   ??? ANavesUSFX_012026Pawn
  ?       ??? Responsabilidad: Nave del jugador, movimiento, disparo
  ?
  ??? AGameModeBase (Unreal Base)
      ??? ANavesUSFX_012026GameMode
          ??? Responsabilidad: Reglas del juego, asignacion de Pawn
```

## Proximas Mejoras (TODO)

- [ ] Agregar enemigos IA
- [ ] Sistema de puntuacion y vidas
- [ ] Niveles/Mapas adicionales
- [ ] Efectos visuales (particulas, explosiones)
- [ ] Sonidos y musica
- [ ] UI/HUD (salud, puntos, etc.)
- [ ] Powerups y mejoras
- [ ] Multijugador

## Licencia

Este proyecto es educativo y fue desarrollado como parte del curso de Unreal Engine en USFX.

## Contacto y Soporte

- **Autor**: Cristian Bravo
- **GitHub**: https://github.com/cristianbravocm4770845-creator
- **Repositorio**: https://github.com/cristianbravocm4770845-creator/NavesUSFX_012026

## Historial de Cambios

### Version 1.0 - Inicial
- Implementacion base: Pawn controlable
- Sistema de proyectiles con colisiones
- GameMode basico
- Todo el codigo comentado en detalle
- Configuracion de Git LFS

---

**Fecha de Creacion**: Mayo 2026
**Ultima Actualizacion**: 17 de Mayo de 2026
