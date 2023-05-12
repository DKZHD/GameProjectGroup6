// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "DeathScreen.generated.h"

/**
 * 
 */
class UButton;

UCLASS()
class GAMEPROJECTGROUP6_API UDeathScreen : public UUserWidget
{
	GENERATED_BODY()

	//Buttons
	UPROPERTY(EditAnywhere,meta=(BindWidget))
	UButton* Retry;
	UPROPERTY(EditAnywhere,meta=(BindWidget))
	UButton* Menu;
	UPROPERTY(EditAnywhere,meta=(BindWidget))
	UButton* Quit;

	//Button Functionality
	virtual void NativeConstruct() override;
	UFUNCTION()
	void RetryFunction();
	UFUNCTION()
	void MenuFunction();
	UFUNCTION()
	void QuitFunction();
	
	//Input modes
	FInputModeUIOnly UIOnly;
	FInputModeGameOnly Game;
};
