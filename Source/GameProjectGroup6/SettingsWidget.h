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
	UPROPERTY(meta=(BindWidget))
	class UComboBoxString* WindowSettings;
	UFUNCTION()
	void WindowModeFunction(FString SelectedItem, ESelectInfo::Type SelectionType);
	
	
};
