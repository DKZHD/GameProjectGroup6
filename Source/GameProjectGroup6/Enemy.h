// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Enemy.generated.h"
class USoundCue;
class ABardPlayer;
class USphereComponent;
class UDamageHandlingComponent;
class UHealthBardComponent;
class AItems;
class UAnimMontage;
class AEnemyAIController;


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

	//Individual Function when taking damage
	UFUNCTION()
	void OnAnyDamageTaken(AActor* DamagedActor, float Damage, const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser);
	
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

	UFUNCTION(BlueprintCallable)
	void AttackFunction();
	
	UFUNCTION()
		void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
    	                    UPrimitiveComponent* OtherComponent,
    	                    int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UPROPERTY()
	TSubclassOf<UDamageType> BaseDamage;
	
	//Item to spawn
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
    	TSubclassOf<AItems> ItemsToSpawn;
	
	//Bool if enemy is attacking
	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category = "Enemy")
	bool CanAttack;

	//Bool if the enemy is stunned 
	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category = "Enemy")
	bool IsStunned;

	//Droprate of the item
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemy")
	int Droprate;

	//Type of Enemy
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemy")
	bool BowEnemy;

	UPROPERTY()
	bool ItHit;

	//Refference to the item
	UPROPERTY()
	AItems* Item;
	
	//Bard Player
	UPROPERTY()
	ABardPlayer* Bard;

	//Collider
	UPROPERTY(EditAnywhere)
	USphereComponent* Collider;

	UPROPERTY()
	AEnemyAIController* AIController;

	//Play Hit animation
	UPROPERTY(EditAnywhere)
	UAnimMontage* GoblinHit;

	//Sounds
	UPROPERTY(EditAnywhere)
	USoundBase* DamageSound;

	UPROPERTY(EditAnywhere, Category = "Animation")
	UAnimMontage* HitMontage;

	UPROPERTY()
	UAnimInstance* AnimInstance;
	
	// UPROPERTY(EditAnywhere, Category = "Animation")
	// UAnimMontage* StunnedMontage;

	UFUNCTION()
	void AnimNotifyBegin(FName NotifyName, const FBranchingPointNotifyPayload& BranchingPointPayload);
	
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
	

};

