# CONTRIBUTING.md

## Guia para Contribuir al Proyecto NavesUSFX_012026

### Objetivo del Proyecto

Este proyecto es educativo y se centra en desarrollar un videojuego tipo Twin Stick Shooter
en Unreal Engine 4 con C++, manteniendo un codigo bien comentado y documentado.

### Requisitos Previos

1. **Unreal Engine 4.25+** instalado
2. **Visual Studio 2019+** con C++ workload
3. **Git** con **Git LFS** instalado
4. Acceso al repositorio (colaborador)

### Flujo de Trabajo

#### 1. Clonar el Repositorio

```bash
git clone https://github.com/cristianbravocm4770845-creator/NavesUSFX_012026.git
cd NavesUSFX_012026
git lfs pull
```

#### 2. Crear una Rama para tu Trabajo

```bash
# Siempre crear rama desde master actualizado
git checkout master
git pull origin master

# Crear rama con nombre descriptivo
git checkout -b feature/nombre-de-la-caracteristica
# o
git checkout -b bugfix/nombre-del-bug
# o
git checkout -b docs/mejora-documentacion
```

#### 3. Hacer Cambios

**Reglas importantes:**

- ? Todos los cambios en codigo DEBEN estar comentados
- ? Los comentarios deben estar en ESPAÑOL
- ? Explicar QUE hace el codigo, NO como lo hace
- ? Usar comentarios de bloque `/** ... */` para funciones
- ? Usar comentarios de linea `//` para explicaciones cortas
- ? Mantener consistencia con el estilo existente

**Ejemplo de buen comentario:**

```cpp
/**
 * METODO: CalcularDano()
 * 
 * PROPOSITO:
 * Calcula el dano que hace un proyectil al impactar.
 * 
 * PARAMETROS:
 * - velocidad: Velocidad del proyectil (afecta el dano)
 * - tipo: Tipo de dano (fuego, hielo, etc.)
 * 
 * RETORNA:
 * Valor de dano entero a aplicar al objetivo
 * 
 * NOTAS:
 * El dano varia segun el tipo de proyectil.
 * Los objetos estaticos reciben 50% de dano.
 */
float CalcularDano(float velocidad, EDamageType tipo);
```

#### 4. Compilar y Probar

```bash
# Compile en Visual Studio
# O en el editor de Unreal

# Prueba la funcionalidad
# Asegurate de que no hay errores de compilacion
# Prueba en el juego si es posible
```

#### 5. Hacer Commit

```bash
git add .
git commit -m "Tipo de cambio: Descripcion breve

Descripcion detallada de los cambios realizados.
Incluye motivacion, impacto, etc.

Tipos de cambios:
- feat: Nueva caracteristica
- fix: Correccion de bug
- docs: Cambios en documentacion
- style: Cambios de formato (sin logica)
- refactor: Cambios en codigo (sin nuevas features)
- test: Agregar/modificar tests
- chore: Cambios en build, deps, etc.

Ejemplo:
feat: Agregar sistema de enemigos basico

- Implementar clase AEnemy heredando de APawn
- Agregar IA simple (seguir al jugador)
- Implementar colisiones y dano al jugador
- Todo el codigo comentado en detalle"