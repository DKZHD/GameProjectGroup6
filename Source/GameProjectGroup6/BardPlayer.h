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
	UPROPERTY(EditAnywhere, Category="Flute")
	TSubclassOf<class AWeaponBase> Flute;
	UPROPERTY(EditAnywhere, Category="Drum")
	TSubclassOf<AWeaponBase> Drum;
	UPROPERTY(EditAnywhere, Category="Drum")
	TSubclassOf<AActor> DrumStick_BP;
	UPROPERTY(EditAnywhere, Category="Harp")
	TSubclassOf<AWeaponBase> Harp;
	UPROPERTY(EditAnywhere)
	USceneComponent* DrumSpawn;
	UPROPERTY(EditAnywhere)
	class UDamageHandlingComponent* DamageHandlingComponent;
	UPROPERTY()
	AWeaponBase* FluteRef;

	//Handles
	UPROPERTY()
	FTimerHandle Handle;
	UPROPERTY()
	FTimerHandle DrumAOEHandle;

	//Systems
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Flute")
		class UNiagaraSystem* FluteSlash;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Drum")
		class UNiagaraSystem* DrumAOE;

	//Input
	UPROPERTY(EditAnywhere, Category="Input")
		class UInputMappingContext* IMC;
	UPROPERTY(EditAnywhere, Category="Input")
		class UInputAction* Move;
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
	void DoDamage(AActor* DamagedActor, float BaseDamage, AController* EventInstigator, AActor* DamageCauser, TSubclassOf<class UDamageType> DamageTypeClass);
	UFUNCTION()
	void ActivateMovement();
	UFUNCTION()
	void PlayHitAnim(AActor* DamagedActor, float Damage, const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser);
	UFUNCTION()
	void WhenCompleted(UAnimMontage* Montage, bool bInterrupted);
	UFUNCTION()
	void SpawnDrumAOE();
	UFUNCTION()
	void PauseFunction();
	UFUNCTION()
	void AnimNotifyBegin(FName NotifyName, const FBranchingPointNotifyPayload& BranchingPointPayload);

	//Variables
	int WeaponNumber=1;
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
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	bool IsDrumming;
	UPROPERTY()
	bool IsFluting;
	UPROPERTY()
	UAnimInstance* AnimInstance;
	FHitResult Hit;
	FCollisionQueryParams TraceHit;
	float LerpAlpha;
	float TimeSpent;
	UPROPERTY(EditAnywhere, Category="User Widgets")
	TSubclassOf<UUserWidget> PauseScreen;
	UPROPERTY(EditAnywhere, Category="User Widgets")
	TSubclassOf<UUserWidget> DeathScreen;
	UPROPERTY()
	UUserWidget* PauseScreenRef;
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

	//Spawned Components
	UPROPERTY()
	AActor* SpawnedFlute = nullptr;
	UPROPERTY()
	AActor* SpawnedDrum = nullptr;
	UPROPERTY()
	AActor* DrumStick1 = nullptr;
	UPROPERTY()
	AActor* DrumStick2 = nullptr;

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
