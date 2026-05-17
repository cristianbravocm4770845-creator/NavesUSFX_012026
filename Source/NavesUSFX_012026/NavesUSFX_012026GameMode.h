// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "NavesUSFX_012026GameMode.generated.h"

// ============================================================================
// CLASE: ANavesUSFX_012026GameMode
// ============================================================================
/**
 * DESCRIPCIÓN GENERAL:
 * ANavesUSFX_012026GameMode es el "Game Mode" o "Modo de Juego" de este proyecto.
 * 
 * ¿QUÉ ES UN GAME MODE EN UNREAL ENGINE?
 * El Game Mode es un objeto especial que define las REGLAS GENERALES del juego:
 *   - Cuál es el Pawn (personaje controlable) que usan los jugadores
 *   - Cuál es el PlayerController (controlador del jugador)
 *   - Cuál es el HUD (interface en pantalla)
 *   - Cuándo comienza y termina la partida
 *   - Cómo funciona el sistema de puntos/rondas
 *   - etc.
 * 
 * PATRÓN DE DISEÑO:
 * El Game Mode es un "Singleton" (existe UNA SOLA instancia por nivel).
 * Se crea automáticamente al cargar un mapa.
 * El motor garantiza que siempre existe exactamente uno en memoria.
 * 
 * RESPONSABILIDADES DE ESTA CLASE:
 * 1. ASIGNAR EL PAWN POR DEFECTO
 *    ? Le dice al motor: "Cuando un jugador entra, crea esto para que lo controle"
 *    ? En este caso: ANavesUSFX_012026Pawn (la nave del jugador)
 * 
 * 2. MANTENER LAS REGLAS DEL JUEGO
 *    ? Aunque en esta versión es minimalista
 *    ? Un Game Mode más complejo podría manejar:
 *       - Sistema de vidas
 *       - Sistema de puntuación
 *       - Condiciones de victoria/derrota
 *       - Gestión de olas de enemigos
 *       - Temporizadores de ronda
 * 
 * JERARQUÍA DE CLASES:
 * AActor (clase base de todo)
 *   ?? AGameModeBase (clase base ligera de Game Modes)
 *       ?? ANavesUSFX_012026GameMode (ESTA CLASE)
 * 
 * TIPO DE PROYECTO:
 * Este es un "Twin Stick Shooter" - juego de vista superior donde:
 *   - El jugador controla una nave
 *   - Puede moverse en X-Y (plano horizontal)
 *   - Puede disparar proyectiles en 8 direcciones
 *   - Debe evitar enemigos o destruirlos
 */


// ============================================================================
// ESPECIFICADORES DE CLASE
// ============================================================================
// MinimalAPI: Exporta solo las funciones virtuales necesarias
//             Reduce el tamaño del binario compilado

UCLASS(MinimalAPI)
class ANavesUSFX_012026GameMode : public AGameModeBase
{
	GENERATED_BODY()

	// =========================================================================
	// MÉTODOS PÚBLICOS
	// =========================================================================

	/**
	 * CONSTRUCTOR: ANavesUSFX_012026GameMode::ANavesUSFX_012026GameMode()
	 * 
	 * TIPO: Constructor
	 * ACCESO: Público
	 * EJECUTADO: Una sola vez cuando el GameMode se instancia en el nivel
	 * 
	 * RESPONSABILIDAD PRINCIPAL:
	 * Asignar cuál será el "Pawn por defecto" del jugador.
	 * 
	 * QUÉ ES "PAWN POR DEFECTO" (DefaultPawnClass)?
	 * Es la clase que Unreal Engine instantaneará automáticamente
	 * para que el jugador la controle cuando entre al nivel.
	 * 
	 * FLUJO:
	 * 1. Nivel comienza a cargar
	 * 2. Motor crea una instancia de este GameMode
	 * 3. Se ejecuta este constructor
	 * 4. Se lee DefaultPawnClass
	 * 5. Motor crea una instancia de ANavesUSFX_012026Pawn
	 * 6. El PlayerController asume el control de ese Pawn
	 * 7. El jugador puede moverse y disparar con la nave
	 * 
	 * DETALLE TÉCNICO:
	 * DefaultPawnClass es una propiedad heredada de AGameModeBase.
	 * Es de tipo: TSubclassOf<APawn>
	 * Lo que significa: "Un puntero a una CLASE (no instancia) derivada de APawn"
	 * 
	 * COMPARACIÓN:
	 * - DefaultPawnClass = Plano/Plano (especifica QUÉ clase usar)
	 * - Pawn actual = Casa real (instancia creada del plano)
	 * 
	 * EN UNREAL EDITOR:
	 * Este constructor se ejecuta:
	 *   - Al presionar "Play" para probar el nivel
	 *   - Al cargar un nivel guardado
	 *   - Al ser instanciado desde un Blueprint
	 * 
	 * CÓDIGO EN CONSTRUCTOR:
	 * DefaultPawnClass = ANavesUSFX_012026Pawn::StaticClass();
	 * 
	 * DESGLOSE:
	 * - ANavesUSFX_012026Pawn = La clase de la nave del jugador
	 * - ::StaticClass() = Función que devuelve la clase en tiempo de ejecución
	 *                     (permite acceder a metadatos de la clase)
	 * - = Asignación al DefaultPawnClass
	 * 
	 * RESULTADO:
	 * El jugador entra al nivel y controla una instancia de ANavesUSFX_012026Pawn
	 */
	ANavesUSFX_012026GameMode();
};



