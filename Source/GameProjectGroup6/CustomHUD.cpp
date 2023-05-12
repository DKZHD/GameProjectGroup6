// Fill out your copyright notice in the Description page of Project Settings.


#include "CustomHUD.h"

#include "BardGameInstance.h"
#include "MainMenu.h"
#include "SettingsWidget.h"
#include "UI.h"
#include "Blueprint/UserWidget.h"
#include "Blueprint/WidgetLayoutLibrary.h"
#include "Components/ComboBoxString.h"
#include "Kismet/GameplayStatics.h"
#include "Runtime/Engine/Classes/GameFramework/GameUserSettings.h"

void ACustomHUD::BeginPlay()
{
	Super::BeginPlay();
	MenuWidget=CreateWidget<UMainMenu>(GetWorld(), MainMenu_BP);
	UIWidget=CreateWidget<UUserWidget>(GetWorld(), UI_BP);
	SettingsScreen=CreateWidget<USettingsWidget>(GetWorld(), Settings_BP);
	UGameUserSettings* UserSettings=Cast<UGameUserSettings>(GEngine->GetGameUserSettings());
	
	OptionSelected=SettingsScreen->WindowSettings->GetSelectedOption();
	SettingsScreen->WindowModeFunction(SettingsScreen->WindowSettings->GetSelectedOption(),ESelectInfo::Direct);
	BardGameInstance=Cast<UBardGameInstance>(GetGameInstance());
	
	if(!BardGameInstance->HasSpawnedMainMenu)
	{
		if(MenuWidget)
		MenuWidget->AddToViewport(0);
		UGameplayStatics::GetPlayerController(GetWorld(),0)->SetInputMode(UIOnly);
		UGameplayStatics::GetPlayerController(GetWorld(),0)->SetShowMouseCursor(true);
		UGameplayStatics::SetGamePaused(this, true);
		BardGameInstance->HasSpawnedMainMenu=true;
	}
	else
	{
		UWidgetLayoutLibrary::RemoveAllWidgets(this);
		if(UIWidget)
		{
			UGameplayStatics::GetPlayerController(GetWorld(),0)->SetInputMode(GameOnly);
			UGameplayStatics::GetPlayerController(GetWorld(),0)->SetShowMouseCursor(false);
			UGameplayStatics::SetGamePaused(this, false);
			UGameplayStatics::GetPlayerCameraManager(this,0)->StartCameraFade(1,0,3,FLinearColor::Black);
			UIWidget->AddToViewport(0);
		}
	}

}

