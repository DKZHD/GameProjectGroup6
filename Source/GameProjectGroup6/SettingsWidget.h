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
	UCheckBox* toggleVSYNC;
	UPROPERTY(meta=(BindWidget))
	UButton* ApplyActiveChanges;
	UPROPERTY(meta=(BindWidget))
	UButton* Return;

	//Get Game Instance
	UPROPERTY()
	UBardGameInstance* BardGameInstance;

	//Get HUD
	UPROPERTY()
	ACustomHUD* CustomHUD;

	//Get Integrated User Settings
	UPROPERTY()
	UGameUserSettings* UserSettings;

	//Functionality
	UFUNCTION()
	void VSyncFunction(bool bIsChecked);
	UFUNCTION()
	void ApplyChangesFunction();
	UFUNCTION()
	void WindowModeFunction(FString SelectedItem, ESelectInfo::Type SelectionType);
	UFUNCTION()
	void GoBack();
	
	
};
