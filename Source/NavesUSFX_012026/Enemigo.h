#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Enemigo.generated.h"

UCLASS()
class NAVESUSFX_012026_API AEnemigo : public AActor
{
    GENERATED_BODY()

public:
    AEnemigo();

    virtual void BeginPlay() override;
    virtual void Tick(float DeltaTime) override;

    // Configura los puntos de patrulla desde código externo (GameMode)
    void ConfigurarPatrulla(const TArray<FVector>& Puntos, float VelocidadMovimiento);

private:
    // Malla visible del enemigo
    UStaticMeshComponent* MeshEnemigo;

    // Puntos de patrulla en el mundo
    TArray<FVector> PuntosPatrulla;

    // Índice del punto destino actual
    int32 IndiceObjetivo;

    // Velocidad de movimiento (unidades/segundo)
    float Velocidad;

    // Si tiene puntos asignados y puede moverse
    bool bPuedePatrullar;

    // Lógica de movimiento ejecutada en Tick
    void MoverHaciaObjetivo(float DeltaTime);
};