// Copyright Epic Games, Inc. All Rights Reserve

// ============================================================================
// INCLUSIONES (Headers)
// ============================================================================
// Estas líneas le dicen al compilador qué archivos de código incluir.
// Cada #include proporciona acceso a clases, funciones y tipos definidos en
// otros archivos del proyecto o del motor Unreal Engine.

#include "NavesUSFX_012026Projectile.h"              // Definición de la clase del proyectil
#include "GameFramework/ProjectileMovementComponent.h" // UProjectileMovementComponent: gestor de movimiento
#include "UObject/ConstructorHelpers.h"               // FObjectFinder: busca assets en Content Browser
#include "Components/StaticMeshComponent.h"           // UStaticMeshComponent: renderiza geometría 3D
#include "Engine/StaticMesh.h"                        // UStaticMesh: recurso de geometría estática


// ============================================================================
// IMPLEMENTACIÓN DEL CONSTRUCTOR
// ============================================================================
/**
 * CONSTRUCTOR: ANavesUSFX_012026Projectile::ANavesUSFX_012026Projectile()
 * 
 * LLAMADA: Se ejecuta UNA SOLA VEZ automáticamente cuando el motor crea
 *          un nuevo proyectil en el mundo del juego.
 * 
 * FLUJO DE EJECUCIÓN:
 * 1. BUSCAR ASSETS en el Content Browser ("staticfindObject" en tiempo de carga)
 * 2. CREAR COMPONENTES dinámicamente
 * 3. CONFIGURAR propiedades de cada componente
 * 4. CONECTAR eventos (enlazar OnHit a la colisión)
 * 5. RETORNAR - El proyectil está listo para existir en el mundo
 * 
 * UBICACIÓN EN LA JERARQUÍA DE CLASES:
 * ANavesUSFX_012026Projectile::Constructor() es parte de la clase Projectile.
 * AActor (clase base) -> ANavesUSFX_012026Projectile (clase actual)
 */
ANavesUSFX_012026Projectile::ANavesUSFX_012026Projectile() 
{
	// ????????????????????????????????????????????????????????????????????
	// PASO 1: BUSCAR Y CARGAR ASSETS (MALLAS 3D)
	// ????????????????????????????????????????????????????????????????????

	/**
	 * FObjectFinder<UStaticMesh>:
	 * Esta es una plantilla de Unreal Engine que busca assets de tipo UStaticMesh
	 * en el Content Browser usando una ruta de recurso.
	 * 
	 * PARÁMETRO: TEXT("/Game/TwinStick/Meshes/TwinStickProjectile.TwinStickProjectile")
	 * Ruta interna de Unreal Engine hacia el asset de malla:
	 *   /Game     = Carpeta raíz del proyecto
	 *   TwinStick = Subcarpeta
	 *   Meshes    = Subcarpeta de mallas
	 *   TwinStickProjectile.TwinStickProjectile = Nombre del asset y su clase
	 * 
	 * RESULTADO:
	 * - ProjectileMeshAsset.Object = puntero a la malla si existe
	 * - ProjectileMeshAsset.Object = nullptr si el asset no se encuentra
	 * 
	 * IMPORTANTE:
	 * static = Esta búsqueda solo ocurre UNA VEZ (en la primera instancia).
	 * Las instancias posteriores reutilizan el resultado cacheado.
	 */
	static ConstructorHelpers::FObjectFinder<UStaticMesh> ProjectileMeshAsset(TEXT("/Game/TwinStick/Meshes/TwinStickProjectile.TwinStickProjectile"));

	// ????????????????????????????????????????????????????????????????????
	// PASO 2: CREAR COMPONENTE PROJECTILEMESH (Renderizado + Colisión)
	// ????????????????????????????????????????????????????????????????????

	/**
	 * CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ProjectileMesh0"))
	 * 
	 * ¿QUÉ ES CreateDefaultSubobject?
	 * Es una función de AActor que crea componentes dinámicamente en el constructor.
	 * Cada componente creado se vincula automáticamente a este actor.
	 * 
	 * ¿QUÉ PARÁMETRO RECIBE?
	 * TEXT("ProjectileMesh0") = Nombre único del componente (usado internamente)
	 *                           Es visible en el editor de Unreal
	 * 
	 * ¿QUÉ RETORNA?
	 * Puntero a UStaticMeshComponent recién creado y listo para configurar
	 * 
	 * ASIGNACIÓN A VARIABLE:
	 * ProjectileMesh = ... ? Se guarda el puntero en la propiedad de miembro
	 *                         para acceso posterior
	 */
	ProjectileMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ProjectileMesh0"));

	/**
	 * SetStaticMesh(ProjectileMeshAsset.Object)
	 * 
	 * PROPÓSITO:
	 * Asigna la geometría 3D (malla visual) que encontramos anteriormente
	 * al componente ProjectileMesh.
	 * 
	 * SIN ESTA LÍNEA:
	 * El componente existiría pero sería invisible en el juego
	 * (sin geometría que renderizar).
	 * 
	 * CON ESTA LÍNEA:
	 * El proyectil mostrará visualmente una esfera pequeña en pantalla.
	 */
	ProjectileMesh->SetStaticMesh(ProjectileMeshAsset.Object);

	/**
	 * SetupAttachment(RootComponent)
	 * 
	 * PROPÓSITO:
	 * Attach = Adjuntar/Vincular un componente a otro en la jerarquía.
	 * 
	 * PARÁMETRO: RootComponent
	 * Este es el componente raíz del actor (que se heredó de AActor).
	 * La primera vez que se ejecuta, RootComponent es nullptr.
	 * 
	 * EN ESTE PUNTO:
	 * RootComponent aún no está definido (es nullptr).
	 * Pero en las siguientes líneas se asignará ProjectileMesh como RootComponent.
	 * 
	 * NOTA DE ORDEN:
	 * Este SetupAttachment() se hace ahora pero tiene efecto después
	 * de que definamos RootComponent = ProjectileMesh;
	 */
	ProjectileMesh->SetupAttachment(RootComponent);

	/**
	 * BodyInstance.SetCollisionProfileName("Projectile")
	 * 
	 * ¿QUÉ ES BodyInstance?
	 * Es la información de física del componente. Aquí se configura:
	 * - Con qué puede colisionar
	 * - Cómo responde a la colisión
	 * - Si está sujeto a gravedad
	 * - etc.
	 * 
	 * PERFIL DE COLISIÓN: "Projectile"
	 * UE4 tiene perfiles de colisión predefinidos que agrupan configuraciones.
	 * El perfil "Projectile" está diseñado para:
	 *   - Colisionar con paredes, terreno, enemigos, etc.
	 *   - Permitir pasar a través de ciertos objetos
	 *   - Ser lo suficientemente eficiente para muchas instancias
	 * 
	 * IMPORTANCIA:
	 * Sin esta configuración, el proyectil podría:
	 *   - No colisionar con nada
	 *   - Colisionar con todo (incluida la nave que lo disparó)
	 *   - Ser demasiado lento si se renderizan muchos
	 */
	ProjectileMesh->BodyInstance.SetCollisionProfileName("Projectile");

	/**
	 * OnComponentHit.AddDynamic(...)
	 * 
	 * ¿QUÉ ES UN EVENTO (Event)?
	 * Es un patrón de diseño donde un objeto notifica a otros cuando algo sucede.
	 * OnComponentHit es un evento que se dispara cada vez que el componente
	 * colisiona con algo.
	 * 
	 * ¿QUÉ SIGNIFICA .AddDynamic(...)?
	 * Se está registrando una función que será llamada automáticamente
	 * cuando ocurra el evento OnComponentHit.
	 * 
	 * SINTAXIS: .AddDynamic(this, &ClassName::MethodName)
	 * - this = El objeto que contendrá la función (en este caso, el proyectil)
	 * - & = Operador de dirección de memoria
	 * - ANavesUSFX_012026Projectile::OnHit = La función a ejecutar
	 * 
	 * RESULTADO:
	 * Cada vez que ProjectileMesh colisiona:
	 *   1. Unreal Engine dispara el evento OnComponentHit
	 *   2. OnComponentHit llama automáticamente a OnHit() de este proyectil
	 *   3. OnHit() ejecuta su lógica (destruir el proyectil, aplicar daño, etc.)
	 * 
	 * ANALÓGÍA:
	 * Es como darle a alguien tu número de teléfono
	 * para que te llame cuando algo importante suceda.
	 */
	ProjectileMesh->OnComponentHit.AddDynamic(this, &ANavesUSFX_012026Projectile::OnHit);

	/**
	 * RootComponent = ProjectileMesh
	 * 
	 * ¿QUÉ ES RootComponent?
	 * Es el componente principal/padre del actor.
	 * La posición, rotación y escala del actor se definen por RootComponent.
	 * 
	 * CONSECUENCIAS DE ESTA ASIGNACIÓN:
	 * - La posición del ACTOR = Posición de ProjectileMesh
	 * - Si mueves ProjectileMesh, el actor se mueve
	 * - Todos los demás componentes se adjuntan a ProjectileMesh
	 * 
	 * NOTA VISUAL EN EDITOR:
	 * En el editor de Unreal, verás una jerarquía:
	 *   ANavesUSFX_012026Projectile (ACTOR)
	 *     ?? ProjectileMesh (COMPONENT - RootComponent)
	 *     ?? ProjectileMovement (COMPONENT)
	 */
	RootComponent = ProjectileMesh;

	// ????????????????????????????????????????????????????????????????????
	// PASO 3: CREAR COMPONENTE PROJECTILEMOVEMENT (Física/Movimiento)
	// ????????????????????????????????????????????????????????????????????

	/**
	 * CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovement0"))
	 * 
	 * SIMILAR A ProjectileMesh, pero este componente NO renderiza geometría.
	 * Su propósito es GESTIONAR EL MOVIMIENTO del proyectil.
	 * 
	 * NOMBRE: UProjectileMovementComponent
	 * - U prefix = Es un componente de Unreal Engine
	 * - ProjectileMovement = Es específico para proyectiles
	 * - Component = Es un componente (se adjunta a actores)
	 * 
	 * CARACTERÍSTICAS:
	 * - Simula física realista (movimiento, gravedad, rebotes)
	 * - Cada fotograma calcula automáticamente la nueva posición
	 * - Se integra directamente con el sistema de física de UE4
	 * - Es mucho más eficiente que calcular movimiento manualmente
	 */
	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovement0"));

	/**
	 * UpdatedComponent = ProjectileMesh
	 * 
	 * ¿QUÉ SIGNIFICA?
	 * Le dice a ProjectileMovement QUÉ COMPONENTE debe mover.
	 * 
	 * EJECUCIÓN EN CADA FOTOGRAMA:
	 * 1. ProjectileMovement calcula velocidad y posición
	 * 2. ProjectileMovement llama a MoveComponent() en ProjectileMesh
	 * 3. ProjectileMesh se traslada a la nueva posición
	 * 4. Como ProjectileMesh es el RootComponent, el ACTOR se mueve también
	 * 
	 * IMPORTANCIA:
	 * Sin esta línea, ProjectileMovement no sabría qué mover.
	 * El proyectil existiría pero no se movería.
	 */
	ProjectileMovement->UpdatedComponent = ProjectileMesh;

	/**
	 * InitialSpeed = 3000.0f
	 * 
	 * ¿QUÉ SIGNIFICA?
	 * Es la velocidad a la que el proyectil se dispara inicialmente.
	 * 
	 * UNIDADES:
	 * 3000.0f = 3000 unidades de Unreal Engine por segundo
	 * 1 unidad ? 1 centímetro en la mayoría de proyectos
	 * Por lo tanto: 3000 unidades/seg = 30 metros/segundo
	 * 
	 * RANGO TÍPICO:
	 * - Muy lento: 500-1000 unidades/seg
	 * - Normal: 2000-3000 unidades/seg
	 * - Muy rápido: 5000+ unidades/seg
	 * 
	 * EFECTO EN JUEGO:
	 * A mayor velocidad, más rápido llega el proyectil a su destino.
	 * Pero también es más difícil esquivarlo.
	 */
	ProjectileMovement->InitialSpeed = 3000.f;

	/**
	 * MaxSpeed = 3000.0f
	 * 
	 * ¿QUÉ SIGNIFICA?
	 * Es la velocidad MÁXIMA que el proyectil puede alcanzar.
	 * 
	 * SI InitialSpeed == MaxSpeed:
	 * El proyectil mantiene una velocidad constante durante su vuelo.
	 * No acelera ni desacelera.
	 * 
	 * SI InitialSpeed < MaxSpeed:
	 * El proyectil podría accelerar gradualmente hasta alcanzar MaxSpeed.
	 * (Si hay aceleración aplicada, pero en este caso no la hay)
	 * 
	 * SI InitialSpeed > MaxSpeed:
	 * El motor automáticamente limita la velocidad a MaxSpeed.
	 * Esto previene bugs o velocidades irrazonables.
	 * 
	 * EN ESTE PROYECTO:
	 * Ambas son iguales = vuelo a velocidad constante y predecible
	 */
	ProjectileMovement->MaxSpeed = 3000.f;

	/**
	 * bRotationFollowsVelocity = true
	 * 
	 * ¿QUÉ SIGNIFICA?
	 * El prefijo "b" indica que es un boolean (verdadero/falso).
	 * Esta propiedad controla si el proyectil rota según su dirección.
	 * 
	 * SI ES TRUE (como en este caso):
	 * - El proyectil SIEMPRE apunta hacia la dirección que se mueve
	 * - Si vuela hacia arriba, rota para mirar hacia arriba
	 * - Si vuela hacia la derecha, rota para mirar a la derecha
	 * - Se ve más realista y natural
	 * 
	 * SI FUERA FALSE:
	 * - El proyectil mantendría su rotación inicial fija
	 * - Aunque se mueva en otra dirección, no rota
	 * - Se ve menos realista (como si estuviera "patinando")
	 * 
	 * VISUALIZACIÓN:
	 * TRUE:  El proyectil [? ? ? ? ?] se rota constantemente
	 * FALSE: El proyectil [? ? ? ? ?] mantiene la misma rotación
	 */
	ProjectileMovement->bRotationFollowsVelocity = true;

	/**
	 * bShouldBounce = false
	 * 
	 * ¿QUÉ SIGNIFICA?
	 * Controla si el proyectil "rebota" cuando toca una superficie.
	 * 
	 * SI ES FALSE (como en este caso):
	 * - El proyectil NO rebota
	 * - Cuando toca algo, se destruye inmediatamente
	 * - Efecto: disparar una bala de cañón que se rompe al impactar
	 * 
	 * SI FUERA TRUE:
	 * - El proyectil REBOTA como una pelota de goma
	 * - Cambia de dirección pero sigue existiendo
	 * - Efecto: disparar una pelota que rebota por el nivel
	 * - Usar para granadas, pelotas mágicas, etc.
	 * 
	 * LÓGICA DE JUEGO:
	 * En "Twin Stick Shooter", los proyectiles son balas que no rebotan.
	 * Por eso bShouldBounce está en FALSE.
	 */
	ProjectileMovement->bShouldBounce = false;

	/**
	 * ProjectileGravityScale = 0.0f
	 * 
	 * ¿QUÉ SIGNIFICA?
	 * Es un multiplicador de gravedad (0.0 = sin gravedad, 1.0 = gravedad normal).
	 * 
	 * SI ES 0.0f (como en este caso):
	 * - NO hay gravedad actuando sobre el proyectil
	 * - El proyectil vuela en línea recta horizontal
	 * - No cae hacia el suelo
	 * - Efecto: disparo plano, como en juegos de arcade
	 * 
	 * SI FUERA 1.0f:
	 * - La gravedad NORMAL actúa sobre el proyectil
	 * - El proyectil desciende gradualmente
	 * - Forma una parábola (como una pelota de basquetbol lanzada)
	 * - Efecto: más realista pero más difícil de controlar
	 * 
	 * SI FUERA 0.5f:
	 * - La gravedad es la mitad de lo normal
	 * - Desciende lentamente
	 * - Efecto: bajo planeta de baja gravedad
	 * 
	 * EN ESTE PROYECTO:
	 * Está en 0.0 porque el juego es una vista superior (top-down)
	 * No tiene sentido tener gravedad "hacia abajo" en una vista cenital.
	 */
	ProjectileMovement->ProjectileGravityScale = 0.f;

	// ????????????????????????????????????????????????????????????????????
	// PASO 4: CONFIGURAR CICLO DE VIDA (Autodestrucción)
	// ????????????????????????????????????????????????????????????????????

	/**
	 * InitialLifeSpan = 3.0f
	 * 
	 * ¿QUÉ SIGNIFICA?
	 * Es el tiempo (en segundos) que el actor existe antes de autodestruirse.
	 * Esta es una propiedad heredada de AActor.
	 * 
	 * FLUJO:
	 * 1. Se crea el proyectil en el mundo
	 * 2. El motor inicia un contador: 0 segundos
	 * 3. El contador aumenta cada fotograma
	 * 4. Cuando contador >= 3.0 segundos:
	 *    a. El motor llama automáticamente a Destroy()
	 *    b. El proyectil se elimina del mundo
	 *    c. Se libera su memoria
	 * 
	 * ¿POR QUÉ?
	 * Si el proyectil nunca colisiona (escapa del mapa), necesita una forma
	 * de eliminarse. Sin InitialLifeSpan, acumularía miles de proyectiles
	 * fantasma invisibles consumiendo memoria y CPU.
	 * 
	 * DURACIÓN TÍPICA:
	 * - Corta (1-2 seg): Para juegos rápidos o armas débiles
	 * - Media (3-5 seg): Para juegos normales (como este)
	 * - Larga (10+ seg): Para proyectiles lentos o mágicos
	 * 
	 * EN ESTE PROYECTO:
	 * 3.0 segundos a 3000 unidades/segundo = 9000 unidades recorridas
	 * Es suficiente para cruzar la mayoría de niveles típicos.
	 */
	InitialLifeSpan = 3.0f;
}

// ============================================================================\n// IMPLEMENTACI\u00d3N DEL MANEJADOR DE EVENTO: OnHit\n// ============================================================================\n/**\n * M\u00c9TODO: void ANavesUSFX_012026Projectile::OnHit(...)\n * \n * TIPO: Manejador de evento (Event handler)\n * EVENTO DISPARADOR: OnComponentHit de ProjectileMesh\n * \n * LLAMADA AUTOM\u00c1TICA:\n * Este m\u00e9todo se ejecuta autom\u00e1ticamente cada vez que ProjectileMesh\n * colisiona con otro componente en el mundo.\n * \n * UBICACI\u00d3N EN EL FLUJO DEL JUEGO:\n * Proyectil creado \u2192 Proyectil se mueve \u2192 Proyectil golpea algo\n *                                                      \u2514\u2500 OnHit() se ejecuta\n * \n * RESPONSABILIDADES:\n * 1. Verificar que la colisi\u00f3n es v\u00e1lida y no es auto-colisi\u00f3n\n * 2. Si el objeto golpeado tiene f\u00edsica, aplicar impulso\n * 3. Destruir el proyectil\n */\nvoid ANavesUSFX_012026Projectile::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)\n{\n\t// \u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\n\t// VALIDACI\u00d3N DE COLISI\u00d3N\n\t// \u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\n\t\n\t// Si la colisi\u00f3n cumple con TODAS las validaciones, se aplica el impulso.\n\t// Si al menos una validaci\u00f3n falla, se salta este bloque.\n\tif ((OtherActor != nullptr) && (OtherActor != this) && (OtherComp != nullptr) && OtherComp->IsSimulatingPhysics())\n\t{\n\t\t// VALIDACI\u00d3N 1: OtherActor != nullptr\n\t\t// El actor golpeado debe existir en memoria (no puede ser nulo).\n\t\t// Si es nullptr, acceder a \u00e9l causer\u00eda un crash.\n\t\t\n\t\t// VALIDACI\u00d3N 2: OtherActor != this\n\t\t// El proyectil no debe golpearse a s\u00ed mismo (evita auto-colisiones).\n\t\t// Esto previene que el proyectil se destruya inmediatamente tras su creaci\u00f3n.\n\t\t\n\t\t// VALIDACI\u00d3N 3: OtherComp != nullptr\n\t\t// El componente del actor debe ser v\u00e1lido (no puede ser nulo).\n\t\t// Sin esto, no habr\u00eda nada a qu\u00e9 aplicar el impulso.\n\t\t\n\t\t// VALIDACI\u00d3N 4: OtherComp->IsSimulatingPhysics()\n\t\t// El componente debe estar activamente simulando f\u00edsica.\n\t\t// Objetos est\u00e1ticos (muros, suelo) tienen esto en false.\n\t\t// Objetos din\u00e1micos (cajas, enemigos) tienen esto en true.\n\t\t// Solo impulsamos objetos que pueden moverse.\n\t\t\n\t\t// Si TODAS las validaciones son verdaderas, aplicamos impulso.\n\t\t/**\n\t\t * AddImpulseAtLocation(Fuerza, Ubicaci\u00f3n)\n\t\t * \n\t\t * GetVelocity() = Velocidad actual del proyectil (direcci\u00f3n + rapidez)\n\t\t * * 20.0f = Multiplicador que amplifica 20 veces la fuerza\n\t\t * GetActorLocation() = Posici\u00f3n del proyectil en el mundo\n\t\t * \n\t\t * EFECTO:\n\t\t * El objeto golpeado recibe un empuj\u00f3n en la direcci\u00f3n del proyectil.\n\t\t * Cuanto m\u00e1s r\u00e1pido iba el proyectil, m\u00e1s fuerte es el empuj\u00f3n.\n\t\t */\n\t\tOtherComp->AddImpulseAtLocation(GetVelocity() * 20.0f, GetActorLocation());\n\t}\n\t// Si alguna validaci\u00f3n falla, se ignora el impulso y solo se destruye el proyectil.\n\n\t// \u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\n\t// DESTRUCCI\u00d3N DEL PROYECTIL - OCURRE SIEMPRE\n\t// \u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\n\t\n\t// Destroy() marca el proyectil para ser eliminado del mundo.\n\t// No lo elimina INMEDIATAMENTE sino al final del fotograma actual.\n\t// Esto es seguro y evita modificar listas durante iteraciones.\n\t// \n\t// CICLO DE VIDA:\n\t// 1. Proyectil se crea\n\t// 2. Proyectil viaja por el nivel\n\t// 3. Proyectil colisiona (OnHit se ejecuta)\n\t// 4. Destroy() marca el proyectil para eliminaci\u00f3n\n\t// 5. Fin del fotograma: el motor elimina el proyectil\n\t// 6. La memoria se libera\n\tDestroy();\n\t// RESULTADO: El proyectil ha desaparecido del mundo\n\t// En el siguiente fotograma, este actor ya no existe\n}"