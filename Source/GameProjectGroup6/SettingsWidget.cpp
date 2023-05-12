// Fill out your copyright notice in the Description page of Project Settings.


#include "SettingsWidget.h"

#include "BardGameInstance.h"
#include "BardPlayer.h"
#include "CustomHUD.h"
#include "MainMenu.h"
#include "Components/Button.h"
#include "Components/CheckBox.h"
#include "Components/ComboBoxString.h"
#include "Components/Slider.h"
#include "Components/TextBlock.h"
#include "Kismet/GameplayStatics.h"
#include "Runtime/Engine/Classes/GameFramework/GameUserSettings.h"


//Add Functionality to button presses, and keep selected active
void USettingsWidget::NativeConstruct()
{
	Super::NativeConstruct();
	BardGameInstance=Cast<UBardGameInstance>(GetGameInstance());
	UserSettings=Cast<UGameUserSettings>(GEngine->GetGameUserSettings());
	CustomHUD=Cast<ACustomHUD>(UGameplayStatics::GetPlayerController(this,0)->GetHUD());
	
	WindowSettings->OnSelectionChanged.AddDynamic(this,&USettingsWidget::WindowModeFunction);
	VsyncCheckBox->OnCheckStateChanged.AddDynamic(this,&USettingsWidget::VSyncFunction);
	HideHUD->OnCheckStateChanged.AddDynamic(this,&USettingsWidget::HideHUDFunction);
	VolumeSlider->OnValueChanged.AddDynamic(this,&USettingsWidget::VolumeChanged);
	Return->OnClicked.AddDynamic(this,&USettingsWidget::GoBack);

	
	VolumeSlider->SetValue(BardGameInstance->VolumeLevel);
	VolumeAmount->SetText(FText::FromString(FString::FromInt(FMath::FloorToInt(BardGameInstance->VolumeLevel*100))));
	VsyncCheckBox->SetIsChecked(BardGameInstance->VSyncBox);
	HideHUD->SetIsChecked(BardGameInstance->HideHUDGameInstance);
	WindowSettings->SetSelectedOption(BardGameInstance->WindowState);
	
	if(!WindowSettings)
		GEngine->AddOnScreenDebugMessage(-1,2.f,FColor::Red,"Can't find");
	else
	{
		GEngine->AddOnScreenDebugMessage(-1,2.f,FColor::Red,"Found IT!");
	}
}

//VSync CheckBox
void USettingsWidget::VSyncFunction(bool bIsChecked)
{
	if(bIsChecked)
	{
		UserSettings->SetVSyncEnabled(true);
		UserSettings->ApplySettings(true);
		UserSettings->SaveSettings();
	}
	else
	{
		UserSettings->SetVSyncEnabled(false);
		UserSettings->ApplySettings(true);
		UserSettings->SaveSettings();
	}
	BardGameInstance->VSyncBox=VsyncCheckBox->IsChecked();
}

void USettingsWidget::HideHUDFunction(bool bIsChecked)
{
	if(bIsChecked)
	{
		BardGameInstance->HideHUDGameInstance=true;
		UserSettings->ApplySettings(true);
		UserSettings->SaveSettings();
	}
	if(!bIsChecked)
	{
		BardGameInstance->HideHUDGameInstance=false;
		UserSettings->ApplySettings(true);
		UserSettings->SaveSettings();
	}
		
}

//Change window mode functionality
void USettingsWidget::WindowModeFunction(FString SelectedItem, ESelectInfo::Type)
 {
 	UserSettings=Cast<UGameUserSettings>(GEngine->GetGameUserSettings());
 	if(UserSettings)
 	{
 			if(SelectedItem=="Windowed")
 			{
 				UserSettings->SetFullscreenMode(EWindowMode::Windowed);
 				BardGameInstance->WindowState="Windowed";
 				UserSettings->ApplySettings(true);
 				UserSettings->SaveSettings();
 			}
         	if(SelectedItem=="Borderless Windowed")
         	{
         		UserSettings->SetFullscreenMode(EWindowMode::WindowedFullscreen);
         		BardGameInstance->WindowState="Borderless Windowed";
         		UserSettings->ApplySettings(true);
         		UserSettings->SaveSettings();
         	}
         	if(SelectedItem=="Fullscreen")
         	{
         		UserSettings->SetFullscreenMode(EWindowMode::Fullscreen);
         		BardGameInstance->WindowState="Fullscreen";
         		UserSettings->ApplySettings(true);
         		UserSettings->SaveSettings();
         	}
 		
 	}
 }

//Return button
void USettingsWidget::GoBack()
{
	UBardGameInstance* GameInstance=Cast<UBardGameInstance>(GetGameInstance());
	if(CustomHUD->MenuWidget->OpenedFromMenu)
	{
		CustomHUD->MenuWidget->AddToViewport();
		CustomHUD->MenuWidget->OpenedFromMenu=false;
	}
	
	else if(GameInstance->HasSpawnedMainMenu)
	{
		ABardPlayer* BardPlayer=Cast<ABardPlayer>(UGameplayStatics::GetPlayerCharacter(GetWorld(),0));
		if(BardPlayer)
		BardPlayer->PauseScreenRef->AddToViewport(0);
	}
	if(this)
	this->RemoveFromParent();
}
//Volume Slider
void USettingsWidget::VolumeChanged(float value)
{
	UGameplayStatics::SetSoundMixClassOverride(GetWorld(),SoundMix,Master,value);
	UGameplayStatics::PushSoundMixModifier(GetWorld(),SoundMix);
	BardGameInstance->VolumeLevel=value;
	VolumeAmount->SetText(FText::FromString(FString::FromInt(FMath::FloorToInt(value*100))));
}

