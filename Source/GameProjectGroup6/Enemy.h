// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Enemy.generated.h"

UCLASS()
class GAMEPROJECTGROUP6_API AEnemy : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AEnemy();
	

	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category = "Enemy")
		bool CanAttack;
		
	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category = "Enemy")
		bool IsStunned;
	

	FTimerHandle Handle;
	FTimerHandle GravityHandle;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
    UFUNCTION()
        void ChangeMovementMode();

	UFUNCTION()
		void OnRadialDamage(AActor* DamagedActor, float Damage, const class UDamageType* DamageType, FVector Origin, FHitResult HitInfo, class AController* InstigatedBy, AActor* DamageCauser);

	UFUNCTION()
		void ResetStun();

	UFUNCTION()
		void Die();

private:
	
	UPROPERTY(VisibleAnywhere)
		class UDamageHandlingComponent* DamageHandling;
	
	UPROPERTY(VisibleAnywhere)
		class UHealthBardComponent* HealthBarWidget;
};
