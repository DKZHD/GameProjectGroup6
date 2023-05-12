// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PauseScreen.generated.h"

/**
 * 
 */
class UButton;

UCLASS()
class GAMEPROJECTGROUP6_API UPauseScreen : public UUserWidget
{
	GENERATED_BODY()
	
	//Buttons
	UPROPERTY(EditAnywhere,meta=(BindWidget))
	UButton* ResumeGame;
	UPROPERTY(EditAnywhere,meta=(BindWidget))
	UButton* MainMenu;
	UPROPERTY(EditAnywhere,meta=(BindWidget))
	UButton* OptionsButton;

	//Sound
	UPROPERTY(EditAnywhere)
	USoundBase* ClickSound;
	
	//Functions
	virtual void NativeConstruct() override;
	UFUNCTION()
	void ResumeButtonClicked();
	UFUNCTION()
	void MenuButtonClicked();
	UFUNCTION()
	void OptionsButtonClicked();

	//Input Mode
	FInputModeGameOnly Game;
	FInputModeUIOnly UI;
	

};
