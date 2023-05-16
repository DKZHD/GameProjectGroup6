// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "BardPlayer.generated.h"

class AArrow;
class USpringArmComponent;
class UCameraComponent;
class AWeaponBase;
class UDamageHandlingComponent;
class UNiagaraSystem;
class UInputAction;
class UInputMappingContext;
class ACustomHUD;

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
	USpringArmComponent* SpringArm;
	UPROPERTY(EditAnywhere)
	UCameraComponent* Camera;

	//Weapon Blueprints
	UPROPERTY(EditAnywhere, Category="Flute")
	TSubclassOf<AWeaponBase> Flute;
	UPROPERTY(EditAnywhere, Category="Drum")
	TSubclassOf<AWeaponBase> Drum;
	UPROPERTY(EditAnywhere, Category="Drum")
	TSubclassOf<AActor> DrumStick_BP;
	UPROPERTY(EditAnywhere, Category="Harp")
	TSubclassOf<AWeaponBase> Harp;
	UPROPERTY(EditAnywhere, Category="Harp")
	TSubclassOf<AArrow> Arrow;

	//Additional Components 
	UPROPERTY(EditAnywhere)
	USceneComponent* DrumSpawn;
	UPROPERTY(EditAnywhere)
	USceneComponent* HarpSpawn;
	UPROPERTY(EditAnywhere)
	UDamageHandlingComponent* DamageHandlingComponent;
	
	//Spawned Components
	UPROPERTY()
	AWeaponBase* FluteRef;
	UPROPERTY()
	AActor* SpawnedHarp=nullptr;
	UPROPERTY()
	AActor* SpawnedFlute = nullptr;
	UPROPERTY()
	AArrow* ArrowRef=nullptr;
	UPROPERTY()
	AActor* SpawnedDrum = nullptr;
	UPROPERTY()
	AActor* DrumStick1 = nullptr;
	UPROPERTY()
	AActor* DrumStick2 = nullptr;
	
	//Handles
	UPROPERTY()
	FTimerHandle Handle;
	UPROPERTY()
	FTimerHandle DrumAOEHandle;

	//Systems
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Flute")
		UNiagaraSystem* FluteSlash;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Drum")
		UNiagaraSystem* DrumAOE;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	//Inputs
	UPROPERTY(EditAnywhere, Category="Input")
		UInputMappingContext* IMC;
	UPROPERTY(EditAnywhere, Category="Input")
		UInputAction* Move;
	UPROPERTY(EditAnywhere, Category="Input")
		UInputAction* CombatAction;
	UPROPERTY(EditAnywhere, Category="Input")
		UInputAction* SwapWeapon;
	UPROPERTY(EditAnywhere, Category="Input")
		UInputAction* Pause;

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
	void ActivateMovement();
	UFUNCTION()
	void SpawnDrumAOE();
	UFUNCTION()
	void PauseFunction();
	UFUNCTION()
	void DespawnHarp();
	UFUNCTION()
	void DrumAgain();
	
	//Variables
	UPROPERTY()
	FVector Position;
	UPROPERTY()
	FVector LineTraceStart;
	UPROPERTY()
	FVector LineTraceEnd;
	UPROPERTY()
	FRotator Direction;
	UPROPERTY()
	float AnimDuration;
	UPROPERTY()
	float DrumCooldown;
	UPROPERTY()
	bool IsDrumming;
	UPROPERTY()
	bool IsFluting;
	UPROPERTY()
	bool IsHarping;
	UPROPERTY()
	int WeaponNumber=1;
	UPROPERTY()
	FHitResult Hit;
	FCollisionQueryParams TraceHit;
	UPROPERTY()
	ACustomHUD* CustomHUD;
	UPROPERTY()
	float TimeSpent;
	UPROPERTY(BlueprintReadOnly)
	bool DrumAnimation;
	
	//Animations
	UPROPERTY()
	UAnimInstance* AnimInstance;
	UPROPERTY(EditAnywhere, Category = "Custom Animations")
	UAnimMontage* DrumAttack;
	UPROPERTY(EditAnywhere, Category = "Custom Animations")
	UAnimMontage* FluteAttack;
	UPROPERTY(EditAnywhere, Category = "Custom Animations")
	UAnimMontage* HarpAttack;
	UPROPERTY(EditAnywhere, Category = "Custom Animations")
	UAnimMontage* HitAnim;
	UPROPERTY(EditAnywhere, Category = "Custom Animations")
	UAnimMontage* HarpRelease;

	//Animation Functions
	UFUNCTION()
	void AnimNotifyBegin(FName NotifyName, const FBranchingPointNotifyPayload& BranchingPointPayload);
	UFUNCTION()
	void WhenCompleted(UAnimMontage* Montage, bool bInterrupted);
	UFUNCTION()
	void PlayHitAnim(AActor* DamagedActor, float Damage, const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser);

	//Widgets
	UPROPERTY(EditAnywhere, Category="User Widgets")
	TSubclassOf<UUserWidget> PauseScreen;
	UPROPERTY(EditAnywhere, Category="User Widgets")
	TSubclassOf<UUserWidget> DeathScreen;
	UPROPERTY()
	UUserWidget* PauseScreenRef;

	//Miscellaneous
	UPROPERTY(EditAnywhere, Category="Damage Type")
	TSubclassOf<UDamageType> BaseDamageType;
	UPROPERTY()
	APlayerCameraManager* CameraManager;
	UPROPERTY(EditAnywhere, Category="Drum")
	TSubclassOf<UCameraShakeBase> BP_DrumShake;

	//Sounds
	UPROPERTY(EditAnywhere, Category="Harp")
	USoundBase* Harp1;
	UPROPERTY(EditAnywhere, Category="Harp")
	USoundBase* Harp2;
	UPROPERTY(EditAnywhere, Category="Harp")
	USoundBase* Harp3;
	UPROPERTY(EditAnywhere, Category="Harp")
	USoundBase* HarpReleased1;
	UPROPERTY(EditAnywhere, Category="Harp")
	USoundBase* HarpReleased2;
	UPROPERTY(EditAnywhere, Category="Harp")
	USoundBase* HarpReleased3;

	//Bools for Sounds
	UPROPERTY()
	bool bHarpSound1;
	UPROPERTY()
	bool bHarpSound2;
	UPROPERTY()
	bool bHarpSound3;
	
	//Ignored
	UPROPERTY()
	TArray<AActor*> IgnoredActors;


};
