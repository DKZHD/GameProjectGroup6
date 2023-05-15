// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Enemy.generated.h"
class ABardPlayer;
class USphereComponent;
class UDamageHandlingComponent;
class UHealthBardComponent;
class AItems;

UCLASS()
class GAMEPROJECTGROUP6_API AEnemy : public ACharacter
{
	GENERATED_BODY()

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	
	// Sets default values for this character's properties
	AEnemy();
	
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

	UFUNCTION()
	void TakenOver();

	
	TSubclassOf<UDamageType> BaseDamage;
	
	//Bool if enemy is attacking
	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category = "Enemy")
	bool CanAttack;

	//Bool if the enemy is stunned 
	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category = "Enemy")
	bool IsStunned;

	//Droprate of the item
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemy")
	int Droprate;

	//Refference to the item
	UPROPERTY()
	AItems* Item;

	//Item to spawn
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	TSubclassOf<AItems> ItemsToSpawn;

	//Bard Player
	UPROPERTY()
	ABardPlayer* Bard;

	//Collider
	UPROPERTY(EditAnywhere)
	USphereComponent* Collider;

	UPROPERTY()
	class AEnemyAIController* AIController;
	
	
	//Handles
	FTimerHandle Handle;
	FTimerHandle GravityHandle;

private:

	//Component to handle damage
	UPROPERTY(VisibleAnywhere)
	UDamageHandlingComponent* DamageHandling;

	// Component to handle the healthbar
	UPROPERTY(VisibleAnywhere)
	UHealthBardComponent* HealthBarWidget;

	//Checks for overlap
	UFUNCTION()
		void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
    	                    UPrimitiveComponent* OtherComponent,
    	                    int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

};
