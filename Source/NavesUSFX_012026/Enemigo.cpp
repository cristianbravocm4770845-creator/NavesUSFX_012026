#include "Enemigo.h"
#include "Engine/StaticMesh.h"
#include "UObject/ConstructorHelpers.h"

AEnemigo::AEnemigo()
{
    PrimaryActorTick.bCanEverTick = true;

    // Crear componente de malla
    MeshEnemigo = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshEnemigo"));
    RootComponent = MeshEnemigo;

    // Cargar la malla básica Sphere de Engine Content (siempre disponible en UE4)
    static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshRef(
        TEXT("/Engine/BasicShapes/Sphere.Sphere")
    );
    if (MeshRef.Succeeded())
    {
        MeshEnemigo->SetStaticMesh(MeshRef.Object);
    }

    // Valores por defecto
    IndiceObjetivo = 0;
    Velocidad = 300.f;
    bPuedePatrullar = false;
}

void AEnemigo::BeginPlay()
{
    Super::BeginPlay();
    // Si ya tiene puntos configurados antes del Begin, marcar listo
    if (PuntosPatrulla.Num() > 1)
    {
        bPuedePatrullar = true;
    }
}

void AEnemigo::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    if (bPuedePatrullar)
    {
        MoverHaciaObjetivo(DeltaTime);
    }
}

void AEnemigo::ConfigurarPatrulla(const TArray<FVector>& Puntos, float VelocidadMovimiento)
{
    if (Puntos.Num() < 2)
    {
        UE_LOG(LogTemp, Warning, TEXT("AEnemigo: Se necesitan al menos 2 puntos de patrulla."));
        return;
    }

    PuntosPatrulla = Puntos;
    Velocidad = VelocidadMovimiento;
    IndiceObjetivo = 0;
    bPuedePatrullar = true;

    // Teletransportar al primer punto
    SetActorLocation(PuntosPatrulla[0]);
}

void AEnemigo::MoverHaciaObjetivo(float DeltaTime)
{
    if (PuntosPatrulla.Num() == 0) return;

    const FVector PosActual = GetActorLocation();
    const FVector PosDestino = PuntosPatrulla[IndiceObjetivo];
    const FVector Direccion = (PosDestino - PosActual).GetSafeNormal();
    const float   Distancia = FVector::Dist(PosActual, PosDestino);
    const float   Paso = Velocidad * DeltaTime;

    if (Distancia <= Paso)
    {
        // Llegó al punto: saltar exactamente y avanzar al siguiente
        SetActorLocation(PosDestino);
        IndiceObjetivo = (IndiceObjetivo + 1) % PuntosPatrulla.Num();
    }
    else
    {
        // Moverse hacia el destino
        SetActorLocation(PosActual + Direccion * Paso);
    }

    // Rotar el enemigo en la dirección de movimiento
    if (!Direccion.IsNearlyZero())
    {
        const FRotator RotObjetivo = Direccion.Rotation();
        SetActorRotation(RotObjetivo);
    }
}