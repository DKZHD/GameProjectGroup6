// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Arrow.generated.h"

class AEnemyAIController;
class UNiagaraComponent;
class UProjectileMovementComponent;
class UBoxComponent;

UCLASS()
class GAMEPROJECTGROUP6_API AArrow : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AArrow();
    // Called every frame
    virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* ArrowMesh;
	UPROPERTY(EditAnywhere)
	UBoxComponent* CollisionBox;
	UPROPERTY(EditAnywhere)
	UProjectileMovementComponent* ProjectileMovementComponent;
	UPROPERTY(EditAnywhere)
	UNiagaraComponent* Particle;
	UPROPERTY(EditAnywhere)
	float Damage;
	UPROPERTY(EditAnywhere)
	TSubclassOf<UDamageType> DamageType;
	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* Root;
	UPROPERTY(EditAnywhere)
	AEnemyAIController* EnemyController;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Arrow")
	bool EnemyFired;
	

	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
					UPrimitiveComponent* OtherComponent,
					int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

};
