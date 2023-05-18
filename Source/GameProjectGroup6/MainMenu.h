// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MainMenu.generated.h"

/**
 * 
 */
class UButton;
class ACustomHUD;

UCLASS()
class GAMEPROJECTGROUP6_API UMainMenu : public UUserWidget
{
	GENERATED_BODY()
public:
	
	//Widget Components
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UButton* StartGame;
	UPROPERTY(EditAnywhere,meta=(BindWidget))
	UButton* ExitGame;
	UPROPERTY(EditAnywhere,meta=(BindWidget))
	UButton* Settings;

	//Get HUD
	UPROPERTY()
	ACustomHUD* HUD;

	UPROPERTY()
	bool OpenedFromMenu=false;
	
	//Functions 
	virtual void NativeConstruct() override;
	UFUNCTION()
		void StartGameButtonClicked();
	UFUNCTION()
		void SettingsButton();
	UFUNCTION()
		void EndGameClicked();
	UFUNCTION()
		void RemoveMainMenu();
};
