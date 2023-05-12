// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "CustomHUD.generated.h"


/**
 * 
 */
class USettingsWidget;
class UMainMenu;
class UUserWidget;
class USettingsWidget;
class UBardGameInstance;
class UUI;

UCLASS()
class GAMEPROJECTGROUP6_API ACustomHUD : public AHUD
{
	GENERATED_BODY()
	
protected:
	
	virtual void BeginPlay() override;
	
public:
	
	//Widgets
	UPROPERTY(EditAnywhere)
	TSubclassOf<UUserWidget> MainMenu_BP;
	UPROPERTY(EditAnywhere)
	TSubclassOf<UUserWidget> UI_BP;
	UPROPERTY(EditAnywhere)
	TSubclassOf<USettingsWidget> Settings_BP;
	UPROPERTY()
	UMainMenu* MenuWidget;
	UPROPERTY()
	UUI* UIWidget;
	UPROPERTY()
	USettingsWidget* SettingsScreen;
	
	//GameInstance
	UPROPERTY()
	UBardGameInstance* BardGameInstance;
	
	//Save Screen Resolution
	UPROPERTY()
	FString OptionSelected;
	
	//InputModes
	FInputModeGameOnly GameOnly;
	FInputModeUIOnly UIOnly;

	

};
