// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "BardPlayer.generated.h"

UCLASS()
class GAMEPROJECTGROUP6_API ABardPlayer : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ABardPlayer();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//Components
	UPROPERTY(EditAnywhere)
	class USpringArmComponent* SpringArm;
	UPROPERTY(EditAnywhere)
	class UCameraComponent* Camera;
	//Weapons
	UPROPERTY(EditAnywhere)
	TSubclassOf<class AWeaponBase> Flute;
	UPROPERTY(EditAnywhere)
	TSubclassOf<class AWeaponBase> Drum;
	UPROPERTY(EditAnywhere)
	TSubclassOf<AWeaponBase> Harp;
	UPROPERTY(EditAnywhere)
	USceneComponent* DrumSpawn;
	UPROPERTY(EditAnywhere)
	class UDamageHandlingComponent* DamageHandlingComponent;

	//Handles
	FTimerHandle Handle;

	//Systems
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class UNiagaraSystem* FluteSlash;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class UNiagaraSystem* DrumAOE;

	//Input
	UPROPERTY(EditAnywhere)
		class UInputMappingContext* IMC;
	UPROPERTY(EditAnywhere)
		class UInputAction* Move;
	UPROPERTY(EditAnywhere)
		UInputAction* CombatAction;
	UPROPERTY(EditAnywhere)
		UInputAction* SwapWeapon;

	//Functions
	UFUNCTION()
	void Movement(const struct FInputActionValue& Value);
	UFUNCTION()
	void CombatFunction();
	UFUNCTION()
	void CombatFunctionChargeClock();
	UFUNCTION()
	void Weaponswap();
	UFUNCTION()
	void CombatFunctionRelease();
	UFUNCTION()
	void DoDamage(AActor* DamagedActor, float BaseDamage, AController* EventInstigator, AActor* DamageCauser, TSubclassOf<class UDamageType> DamageTypeClass);
	UFUNCTION()
	void ActivateMovement();
	UFUNCTION()
	void PlayHitAnim(AActor* DamagedActor, float Damage, const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser);


	//Variables
	int WeaponNumber=1;
	FVector Position;
	FVector LineTraceStart;
	FVector LineTraceEnd;
	FRotator Direction;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	bool IsDrumming;

	FHitResult Hit;
	FCollisionQueryParams TraceHit;
	float LerpAlpha;
	float TimeSpent;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UDamageType> BaseDamageType;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		float Health = 5;

	//Ignored
	TArray<AActor*> IgnoredActors;

	//Spawned Components
	AActor* SpawnedFlute=nullptr;
	AActor* SpawnedDrum = nullptr;

	//AnimMontages
	UPROPERTY(EditAnywhere, Category = "Custom Animations")
		UAnimMontage* DrumAttack;
	UPROPERTY(EditAnywhere, Category = "Custom Animations")
		UAnimMontage* FluteAttack;
	UPROPERTY(EditAnywhere, Category = "Custom Animations")
		UAnimMontage* HarpAttack;
	UPROPERTY(EditAnywhere, Category = "Custom Animations")
		UAnimMontage* HitAnim;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
