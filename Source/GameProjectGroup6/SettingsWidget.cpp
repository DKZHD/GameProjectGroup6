// Fill out your copyright notice in the Description page of Project Settings.


#include "SettingsWidget.h"

#include "Components/ComboBoxString.h"
#include "Runtime/Engine/Classes/GameFramework/GameUserSettings.h"

void USettingsWidget::NativeConstruct()
{
	Super::NativeConstruct();
	WindowSettings->OnSelectionChanged.AddDynamic(this,&USettingsWidget::WindowModeFunction);
	if(!WindowSettings)
		GEngine->AddOnScreenDebugMessage(-1,2.f,FColor::Red,"Can't find");
	else
	{
		GEngine->AddOnScreenDebugMessage(-1,2.f,FColor::Red,"Found IT!");
	}
}

void USettingsWidget::NativePreConstruct()
{
	Super::NativePreConstruct();
}

void USettingsWidget::WindowModeFunction(FString SelectedItem, ESelectInfo::Type)
 {
 	UGameUserSettings* UserSettings=Cast<UGameUserSettings>(GEngine->GetGameUserSettings());
 	if(UserSettings)
 	{
 			if(SelectedItem=="Windowed")
         	{
 				GEngine->AddOnScreenDebugMessage(-1,2.f,FColor::Red,"Windowed");
         		UserSettings->SetFullscreenMode(EWindowMode::Windowed);
 				UserSettings->ApplySettings(false);
 				UserSettings->SaveSettings();
         	}
         	if(SelectedItem=="Borderless Windowed")
         	{
         		GEngine->AddOnScreenDebugMessage(-1,2.f,FColor::Red,"Borderless");
         		UserSettings->SetFullscreenMode(EWindowMode::WindowedFullscreen);
         		UserSettings->ApplySettings(false);
         		UserSettings->SaveSettings();
         	}
         	if(SelectedItem=="Fullscreen")
         	{
         		UserSettings->SetFullscreenMode(EWindowMode::Fullscreen);
         		UserSettings->ApplySettings(false);
         		UserSettings->SaveSettings();
         	}
 	}
 	
 }

