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

	//Input
	UPROPERTY(EditAnywhere)
		class UInputMappingContext* IMC;
	UPROPERTY(EditAnywhere)
		class UInputAction* Move;
	UPROPERTY(EditAnywhere)
		UInputAction* CombatAction;

	//Functions
	UFUNCTION()
	void Movement(const struct FInputActionValue& Value);

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
