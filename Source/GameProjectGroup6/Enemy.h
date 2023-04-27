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

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemy")
		int Droprate;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
		class AItems* Item;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
		TSubclassOf<AItems> ItemsToSpawn;

	//Bard Player
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	class ABardPlayer* Bard;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	class USphereComponent* Collider;

	

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

	// Changing movement mode to walking
    UFUNCTION()
        void ChangeMovementMode();

	// When the enemy is hit by radial damage
	UFUNCTION()
		void OnRadialDamage(AActor* DamagedActor, float Damage, const class UDamageType* DamageType, FVector Origin, FHitResult HitInfo, class AController* InstigatedBy, AActor* DamageCauser);

	// Function to reset after getting stunned
	UFUNCTION()
		void ResetStun();

	// Function to die
	UFUNCTION()
		void Die();
	
	TSubclassOf<UDamageType> BaseDamage;

private:

	//Component to handle damage
	UPROPERTY(VisibleAnywhere)
		class UDamageHandlingComponent* DamageHandling;

	// Component to handle the healthbar
	UPROPERTY(VisibleAnywhere)
		class UHealthBardComponent* HealthBarWidget;
	UFUNCTION()
    	void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
    	                    UPrimitiveComponent* OtherComponent,
    	                    int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

};
