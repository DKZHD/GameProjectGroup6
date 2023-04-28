// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SettingsWidget.generated.h"



/**
 * 
 */
UCLASS()
class GAMEPROJECTGROUP6_API USettingsWidget : public UUserWidget
{
	GENERATED_BODY()
	
	virtual void NativePreConstruct() override;
public:
	virtual void NativeConstruct() override;
	//Widgets
	UPROPERTY(meta=(BindWidget))
	class UComboBoxString* WindowSettings;
	UPROPERTY(meta=(BindWidget))
	class UCheckBox* toggleVSYNC;
	UPROPERTY(meta=(BindWidget))
	class UButton* ApplyActiveChanges;
	UPROPERTY(meta=(BindWidget))
	class UButton* Return;
	UPROPERTY()
	class UBardGameInstance* BardGameInstance;
	UPROPERTY()
	class ACustomHUD* CustomHUD;

	UPROPERTY()
	UGameUserSettings* UserSettings;
	UFUNCTION()
	void VSyncFunction(bool bIsChecked);
	UFUNCTION()
	void ApplyChangesFunction();
	UFUNCTION()
	void WindowModeFunction(FString SelectedItem, ESelectInfo::Type SelectionType);
	UFUNCTION()
	void GoBack();
	
	
};
