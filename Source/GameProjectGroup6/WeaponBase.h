// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WeaponBase.generated.h"
class ABardPlayer;
class AEnemy;
class UBoxComponent;


UCLASS()
class GAMEPROJECTGROUP6_API AWeaponBase : public AActor
{
	GENERATED_BODY()

protected:
	
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Sets default values for this actor's properties
	AWeaponBase();

	// Components
	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* Mesh;
	ABardPlayer* Bard;
	UPROPERTY()
	AEnemy* Enemy;
	UPROPERTY(EditAnywhere)
	UBoxComponent* FluteCollision;
	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Damage Type to apply 
	TSubclassOf<UDamageType> BaseDamage;

	// Flute overlap function
	UFUNCTION()
	void OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);

};
