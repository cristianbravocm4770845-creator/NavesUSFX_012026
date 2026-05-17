// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "NavesUSFX_012026Projectile.generated.h"

// ============================================================================
// DECLARACIONES ADELANTADAS (Forward Declarations)
// ============================================================================
// Estas incluyen solo las declaraciones de clase sin la definición completa.
// Se utilizan para evitar dependencias circulares y acelerar la compilación.
class UProjectileMovementComponent;  // Componente que maneja el movimiento automático
class UStaticMeshComponent;          // Componente que renderiza la malla 3D

// ============================================================================
// CLASE: ANavesUSFX_012026Projectile
// ============================================================================
/**
 * DESCRIPCIÓN GENERAL:
 * ANavesUSFX_012026Projectile representa los proyectiles (balas/misiles) 
 * disparados por la nave del jugador durante el juego.
 *
 * RESPONSABILIDADES PRINCIPALES:
 *   1. MOVIMIENTO: Viajar en línea recta desde el cañón de la nave hacia
 *      la dirección de disparo a una velocidad constante (3000 unidades/seg).
 *   2. CICLO DE VIDA: Existir en el mundo por un tiempo limitado (3 segundos)
 *      y autodestruirse si no colisiona con nada durante ese tiempo.
 *   3. COLISIÓN: Detectar impactos con otros actores del mundo.
 *   4. REPRESENTACIÓN VISUAL: Mostrar una malla 3D (esfera pequeña) que sea
 *      visible en pantalla y que represente la bala visual y físicamente.
 *
 * HERENCIA:
 * Hereda de AActor, la clase base fundamental de Unreal Engine para todos
 * los objetos que existen en el mundo del juego (tienen posición, rotación,
 * componentes, pueden colisionar, se pueden destruir, etc.).
 *
 * CONTEXTO DEL JUEGO:
 * Este es un juego tipo "Twin Stick Shooter" donde el jugador controla una
 * nave espacial desde una vista superior. Puede moverse en X-Y y disparar
 * proyectiles en cualquier dirección. Los enemigos también pueden disparar,
 * y el objetivo es esquivar o destruir todo lo que se mueva.
 */


// Especificadores de clase:
// config=Game: Indica que esta clase puede leer configuración del archivo DefaultGame.ini
UCLASS(config=Game)
class ANavesUSFX_012026Projectile : public AActor
{
	GENERATED_BODY()

	// =========================================================================
	// SECCIÓN 1: COMPONENTES (Propiedades privadas)
	// =========================================================================
	// Los componentes son "partes" que se pueden agregar a un Actor.
	// Cada componente tiene su propia funcionalidad (renderizar, mover, colisionar).

	private:

		/**
		 * PROPIEDAD: ProjectileMesh (UStaticMeshComponent)
		 * TIPO: Componente de Malla Estática
		 * 
		 * PROPÓSITO:
		 * - Renderizar la geometría 3D visible del proyectil (una esfera pequeña)
		 * - Servir como componente raíz (punto de referencia) del actor
		 * - Manejar la colisión física del proyectil
		 * 
		 * ESPECIFICADORES:
		 * - VisibleAnywhere: Se muestra en el editor de propiedades
		 * - BlueprintReadOnly: Se puede leer desde Blueprints pero no modificar
		 * - Category = Projectile: Se agrupa bajo la categoría "Projectile" en el editor
		 * - AllowPrivateAccess: Los Blueprints pueden acceder a miembros privados
		 * 
		 * CONFIGURACIÓN DINÁMICA:
		 * En el constructor se establece:
		 * - SetStaticMesh(): Carga la malla 3D desde el Content Browser
		 * - BodyInstance.SetCollisionProfileName(): Define qué puede colisionar
		 * - OnComponentHit.AddDynamic(): Se enlaza al evento de colisión
		 */
		UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Projectile, meta = (AllowPrivateAccess = "true"))
		UStaticMeshComponent* ProjectileMesh;

		/**
		 * PROPIEDAD: ProjectileMovement (UProjectileMovementComponent)
		 * TIPO: Componente de Movimiento de Proyectil
		 * 
		 * PROPÓSITO:
		 * - Gestionar automáticamente el movimiento del proyectil cada fotograma
		 * - Simular física (velocidad, gravedad, rebotes) sin código manual
		 * - Mantener el proyectil moviéndose en línea recta a velocidad constante
		 * 
		 * CÓMO FUNCIONA:
		 * En cada fotograma (frame), UProjectileMovementComponent automáticamente:
		 *   1. Lee la velocidad actual y la velocidad máxima del proyectil
		 *   2. Calcula la nueva posición = posición anterior + velocidad * delta_tiempo
		 *   3. Mueve el componente UpdatedComponent (ProjectileMesh) a la nueva posición
		 *   4. Opcionalmente simula gravedad (aquí está desactivada)
		 *   5. Opcionalmente simula rebotes (aquí está desactivado)
		 * 
		 * CONFIGURACIÓN ESPECÍFICA:
		 * - InitialSpeed = MaxSpeed = 3000 unidades/segundo
		 * - bRotationFollowsVelocity = true: El proyectil se rota para mirar hacia
		 *   su dirección de movimiento
		 * - bShouldBounce = false: El proyectil NO rebota con obstáculos
		 * - ProjectileGravityScale = 0: No hay gravedad (vuelo horizontal)
		 * 
		 * ESPECIFICADORES:
		 * - VisibleAnywhere: Se muestra en el editor de propiedades
		 * - BlueprintReadOnly: Se puede leer desde Blueprints pero no modificar
		 * - Category = Movement: Se agrupa bajo la categoría "Movement" en el editor
		 */
		UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Movement, meta = (AllowPrivateAccess = "true"))
		UProjectileMovementComponent* ProjectileMovement;

public:

	// =========================================================================
	// SECCIÓN 2: MÉTODOS PÚBLICOS
	// =========================================================================

	/**
	 * MÉTODO: Constructor ANavesUSFX_012026Projectile()
	 * TIPO: Constructor
	 * ACCESO: Público
	 * 
	 * PROPÓSITO:
	 * Este es el constructor de la clase, se ejecuta UNA SOLA VEZ cuando
	 * se crea una nueva instancia de ANavesUSFX_012026Projectile.
	 * 
	 * RESPONSABILIDADES:
	 * 1. Crear y configurar el componente ProjectileMesh:
	 *    - Busca la malla 3D en el Content Browser (/Game/TwinStick/Meshes/TwinStickProjectile)
	 *    - La asigna al componente
	 *    - La convierte en el componente raíz (RootComponent)
	 *    - Configura el perfil de colisión a "Projectile"
	 * 
	 * 2. Crear y configurar el componente ProjectileMovement:
	 *    - Establece velocidad inicial y máxima en 3000 unidades/seg
	 *    - Desactiva gravedad y rebotes
	 *    - Hace que el proyectil se rote según su dirección
	 * 
	 * 3. Configurar el ciclo de vida:
	 *    - InitialLifeSpan = 3.0 segundos
	 *    - Unreal Engine destruirá automáticamente el actor después de 3 seg
	 * 
	 * 4. Enlazar el evento de colisión:
	 *    - OnComponentHit.AddDynamic() conecta la colisión con OnHit()
	 *    - Cada vez que ProjectileMesh toca algo, se llama a OnHit()
	 * 
	 * FLUJO DE INICIALIZACIÓN:
	 * Constructor() ? Crear componentes ? Buscar assets ? Configurar propiedades
	 *                ? Enlazar eventos ? Proyectil listo para usar
	 */
	ANavesUSFX_012026Projectile();

	/**
	 * MÉTODO: OnHit()
	 * TIPO: Manejador de evento (Event Handler)
	 * ACCESO: Público
	 * EVENTO: Se llama automáticamente por UE4 cuando ocurre una colisión
	 * 
	 * PROPÓSITO:
	 * Responder cuando el proyectil colisiona con algo en el mundo.
	 * Es el punto de entrada de toda la lógica de impacto/colisión del proyectil.
	 * 
	 * LÓGICA ACTUAL:
	 * En la versión actual solo destruye el proyectil.
	 * Pero este es el lugar donde se podría agregar:
	 *   - Aplicar daño al actor golpeado
	 *   - Reproducir efectos de partículas de explosión
	 *   - Reproducir sonidos de impacto
	 *   - Crear fuerzas/impulsos para empujar objetos
	 *   - Registrar puntuación del jugador
	 * 
	 * PARÁMETROS (Estándar de UE4 para OnComponentHit):
	 * 
	 *   HitComp (UPrimitiveComponent*)
	 *   ? El componente del proyectil que está colisionando (ProjectileMesh)
	 *   ? Siempre será ProjectileMesh en esta clase
	 * 
	 *   OtherActor (AActor*)
	 *   ? El actor del mundo que fue golpeado
	 *   ? Podría ser: pared, enemigo, decoración, etc.
	 *   ? Se usa nullptr para verificar si realmente hubo colisión
	 * 
	 *   OtherComp (UPrimitiveComponent*)
	 *   ? El componente específico del OtherActor que fue golpeado
	 *   ? Se usa para aplicar fuerzas o daño al componente exacto
	 * 
	 *   NormalImpulse (FVector)
	 *   ? Vector que apunta en la dirección de la colisión
	 *   ? Útil para calcular rebotes o efectos visuales
	 * 
	 *   Hit (const FHitResult&)
	 *   ? Información detallada de la colisión:
	 *      - Hit.ImpactPoint: coordenadas exactas del impacto
	 *      - Hit.Normal: vector perpendicular a la superficie
	 *      - Hit.Distance: distancia recorrida antes de impactar
	 *      - Hit.Time: porcentaje del movimiento hasta el impacto (0.0-1.0)
	 * 
	 * VALIDACIONES:
	 * - Verifica que OtherActor no sea nullptr (colisión válida)
	 * - Verifica que OtherActor no sea el mismo proyectil (evitar auto-colisión)
	 * - Verifica que OtherComp no sea nullptr
	 * - Verifica que OtherComp está simulando física (para aplicar impulso)
	 * 
	 * PARÁMETRO ESPECIAL: UFUNCTION()
	 * Este macro le dice a UE4 que este método:
	 *   - Puede ser llamado desde Blueprints
	 *   - Puede ser utilizado como manejador de eventos dinámicos
	 *   - Debe ser reflejado en el sistema de reflexión de UE4
	 */
	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	/**
	 * MÉTODO GETTER: GetProjectileMesh()
	 * TIPO: Función de acceso (Accessor/Getter)
	 * ACCESO: Público
	 * RETORNA: Puntero a UStaticMeshComponent (const, no se puede modificar)
	 * 
	 * PROPÓSITO:
	 * Proporcionar acceso de solo lectura al componente ProjectileMesh desde
	 * fuera de la clase. Esto permite que otras clases vean o interroguen
	 * al proyectil pero no lo modifiquen directamente.
	 * 
	 * SPECIFICADOR FORCEINLINE:
	 * FORCEINLINE es una sugerencia al compilador para que reemplace la
	 * llamada a la función con el código real en el sitio de la llamada.
	 * Esto elimina la sobrecarga de llamadas de función para métodos triviales
	 * como este (muy rápido, sin lógica compleja).
	 * 
	 * EJEMPLO DE USO:
	 *   ANavesUSFX_012026Projectile* MyProjectile = ...
	 *   UStaticMeshComponent* Mesh = MyProjectile->GetProjectileMesh();
	 *   // Ahora se puede interrogar a Mesh pero no modificarlo
	 * 
	 * PATRÓN DISEÑO:
	 * Es una buena práctica en C++ y Unreal Engine usar getters para
	 * encapsular datos privados y mantener control sobre cómo se accede a ellos.
	 */
	FORCEINLINE UStaticMeshComponent* GetProjectileMesh() const { return ProjectileMesh; }
	/** Devuelve el componente de movimiento del proyectil. */
	FORCEINLINE UProjectileMovementComponent* GetProjectileMovement() const { return ProjectileMovement; }
};

