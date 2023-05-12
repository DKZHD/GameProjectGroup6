// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SettingsWidget.generated.h"

/**
 * 
 */
class UComboBoxString;
class UCheckBox;
class UButton;
class UBardGameInstance;
class ACustomHUD;
class USlider;
class UTextBlock;

UCLASS()
class GAMEPROJECTGROUP6_API USettingsWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;
	//Widgets
	UPROPERTY(meta=(BindWidget))
	UComboBoxString* WindowSettings;
	UPROPERTY(meta=(BindWidget))
	UCheckBox* VsyncCheckBox;
	UPROPERTY(meta=(BindWidget))
	UCheckBox* HideHUD;
	UPROPERTY(meta=(BindWidget))
	UButton* Return;
	UPROPERTY(meta=(BindWidget))
	USlider* VolumeSlider;
	UPROPERTY(meta=(BindWidget))
	UTextBlock* VolumeAmount;

	//Get Game Instance
	UPROPERTY()
	UBardGameInstance* BardGameInstance;

	//Get HUD
	UPROPERTY()
	ACustomHUD* CustomHUD;

	//Get Integrated User Settings
	UPROPERTY()
	UGameUserSettings* UserSettings;

	//SoundComponents
	UPROPERTY(EditAnywhere)
	USoundMix* SoundMix;
	UPROPERTY(EditAnywhere)
	USoundClass* Master;
	float CurrentVolume;
	

	//Functionality
	UFUNCTION()
	void VSyncFunction(bool bIsChecked);
	UFUNCTION()
	void HideHUDFunction(bool bIsChecked);
	UFUNCTION()
	void WindowModeFunction(FString SelectedItem, ESelectInfo::Type SelectionType);
	UFUNCTION()
	void GoBack();
	UFUNCTION()
	void VolumeChanged(float value);
	
	
};
