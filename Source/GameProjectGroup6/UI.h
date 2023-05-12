// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UI.generated.h"

class UImage;
/**
 * 
 */
class UProgressBar;
class ABardPlayer;

UCLASS()
class GAMEPROJECTGROUP6_API UUI : public UUserWidget
{
	GENERATED_BODY()

	// Called when created
	virtual void NativeConstruct() override;

	// Widgets
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UProgressBar* HP_Bar;
	UPROPERTY(EditAnywhere,meta=(BindWidget))
	UImage* FluteImage;
	UPROPERTY(EditAnywhere,meta=(BindWidget))
	UImage* DrumImage;
	UPROPERTY(EditAnywhere,meta=(BindWidget))
	UImage* HarpImage;
	
	// Reference to player 
	UPROPERTY(EditAnywhere)
	ABardPlayer* Bard;

	// Variable for health in player
	UPROPERTY()
	float Health;

	// Function to adjust Health bar with player's current health
	UFUNCTION(BlueprintPure)
		float GetHealthPercent();
public:
	UFUNCTION()
	void ChangeUIPicture();
};
