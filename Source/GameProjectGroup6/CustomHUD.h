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
		TSubclassOf<UUserWidget> MainMenu_BP;
	UPROPERTY(EditAnywhere)
		TSubclassOf<UUserWidget> UI_BP;
	UPROPERTY()
	class UUserWidget* MenuWidget;
	UPROPERTY()
	class UUserWidget* UIWidget;

	UPROPERTY()
	class UBardGameInstance* BardGameInstance;
	
	FInputModeGameOnly GameOnly;
	FInputModeUIOnly UIOnly;
	UFUNCTION()
	void ClearWidgets();

	FTimerHandle Handle;

};
