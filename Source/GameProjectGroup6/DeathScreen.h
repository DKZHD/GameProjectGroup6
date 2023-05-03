// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "DeathScreen.generated.h"

/**
 * 
 */
UCLASS()
class GAMEPROJECTGROUP6_API UDeathScreen : public UUserWidget
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere,meta=(BindWidget))
	class UButton* Retry;
	UPROPERTY(EditAnywhere,meta=(BindWidget))
	UButton* Menu;
	UPROPERTY(EditAnywhere,meta=(BindWidget))
	UButton* Quit;

	virtual void NativeConstruct() override;
	UFUNCTION()
	void RetryFunction();
	UFUNCTION()
	void MenuFunction();
	UFUNCTION()
	void QuitFunction();
	FInputModeUIOnly UIOnly;
	FInputModeGameOnly Game;
};
