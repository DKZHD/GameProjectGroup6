// Fill out your copyright notice in the Description page of Project Settings.


#include "SettingsWidget.h"

#include "BardGameInstance.h"
#include "CustomHUD.h"
#include "Components/Button.h"
#include "Components/CheckBox.h"
#include "Components/ComboBoxString.h"
#include "Kismet/GameplayStatics.h"
#include "Runtime/Engine/Classes/GameFramework/GameUserSettings.h"

void USettingsWidget::NativeConstruct()
{
	Super::NativeConstruct();
	BardGameInstance=Cast<UBardGameInstance>(GetGameInstance());
	UserSettings=Cast<UGameUserSettings>(GEngine->GetGameUserSettings());
	CustomHUD=Cast<ACustomHUD>(UGameplayStatics::GetPlayerController(this,0)->GetHUD());
	
	WindowSettings->OnSelectionChanged.AddDynamic(this,&USettingsWidget::WindowModeFunction);
	toggleVSYNC->OnCheckStateChanged.AddDynamic(this,&USettingsWidget::VSyncFunction);
	ApplyActiveChanges->OnClicked.AddDynamic(this,&USettingsWidget::ApplyChangesFunction);
	Return->OnClicked.AddDynamic(this,&USettingsWidget::GoBack);
	
	toggleVSYNC->SetIsChecked(BardGameInstance->CheckedBox);
	WindowSettings->SetSelectedOption(BardGameInstance->WindowState);
	
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

void USettingsWidget::VSyncFunction(bool bIsChecked)
{
	if(bIsChecked)
	{
		UserSettings->SetVSyncEnabled(true);
		UserSettings->SaveSettings();
		BardGameInstance->CheckedBox=true;
		UserSettings->ApplySettings(false);
		GEngine->AddOnScreenDebugMessage(-1,2.f,FColor::Red,"Checked");
		
	}
	else
	{
		UserSettings->SetVSyncEnabled(false);
		UserSettings->ApplySettings(false);
		BardGameInstance->CheckedBox=false;
		GEngine->AddOnScreenDebugMessage(-1,2.f,FColor::Red,"Unchecked");
		UserSettings->SaveSettings();
	}
}

void USettingsWidget::ApplyChangesFunction()
{
	UserSettings->ApplySettings(true);
	UserSettings->SaveSettings();
}

void USettingsWidget::WindowModeFunction(FString SelectedItem, ESelectInfo::Type)
 {
 	UserSettings=Cast<UGameUserSettings>(GEngine->GetGameUserSettings());
 	if(UserSettings)
 	{
 			if(SelectedItem=="Windowed")
         	{
 				GEngine->AddOnScreenDebugMessage(-1,2.f,FColor::Red,"Windowed");
         		UserSettings->SetFullscreenMode(EWindowMode::Windowed);
 				UserSettings->ApplySettings(false);
 				BardGameInstance->WindowState="Windowed";
 				UserSettings->SaveSettings();
         	}
         	if(SelectedItem=="Borderless Windowed")
         	{
         		GEngine->AddOnScreenDebugMessage(-1,2.f,FColor::Red,"Borderless");
         		UserSettings->SetFullscreenMode(EWindowMode::WindowedFullscreen);
         		UserSettings->ApplySettings(false);
         		BardGameInstance->WindowState="Borderless Windowed";
         		UserSettings->SaveSettings();
         	}
         	if(SelectedItem=="Fullscreen")
         	{
         		UserSettings->SetFullscreenMode(EWindowMode::Fullscreen);
         		UserSettings->ApplySettings(false);
         		BardGameInstance->WindowState="Fullscreen";
         		UserSettings->SaveSettings();
         	}
 	}
 	
 }

void USettingsWidget::GoBack()
{
	CustomHUD->MenuWidget->AddToViewport();
	RemoveFromParent();
}

