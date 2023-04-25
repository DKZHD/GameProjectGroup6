// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "CustomHUD.generated.h"

/**
 * 
 */
UCLASS()
class GAMEPROJECTGROUP6_API ACustomHUD : public AHUD
{
	GENERATED_BODY()
public:
	ACustomHUD();
protected:
	virtual void BeginPlay() override;
public:
	UPROPERTY(EditAnywhere)
		TSubclassOf<UUserWidget> UI_BP;
	
	FInputModeGameOnly GameOnly;
	UFUNCTION()
	void ClearWidgets();

	FTimerHandle Handle;

};
