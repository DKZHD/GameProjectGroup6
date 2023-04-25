// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MainMenu.generated.h"

/**
 * 
 */
UCLASS()
class GAMEPROJECTGROUP6_API UMainMenu : public UUserWidget
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, meta = (BindWidget))
		class UButton* StartGame;

	virtual void NativeConstruct() override;

	UFUNCTION()
		void StartGameButtonClicked();
};