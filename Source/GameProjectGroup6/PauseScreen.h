// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PauseScreen.generated.h"


/**
 * 
 */
UCLASS()
class GAMEPROJECTGROUP6_API UPauseScreen : public UUserWidget
{
	GENERATED_BODY()
	virtual void NativeConstruct() override;
	UPROPERTY(EditAnywhere,meta=(BindWidget))
	class UButton* ResumeGame;
	UPROPERTY(EditAnywhere,meta=(BindWidget))
	UButton* MainMenu;

	UFUNCTION()
	void ResumeButtonClicked();
	UFUNCTION()
	void MenuButtonClicked();
	
	FInputModeGameOnly Game;
	FInputModeUIOnly UI;
	
	// UPROPERTY(EditAnywhere,meta=(BindWidget))
	// UButton* Settings;
};
