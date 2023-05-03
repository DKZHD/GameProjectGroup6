// Fill out your copyright notice in the Description page of Project Settings.


#include "PauseScreen.h"

#include "BardGameInstance.h"
#include "CustomHUD.h"
#include "SettingsWidget.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"

void UPauseScreen::NativeConstruct()
{
	Super::NativeConstruct();
	UGameplayStatics::GetPlayerController(this,0)->SetShowMouseCursor(true);
	UGameplayStatics::SetGamePaused(this, true);
	UGameplayStatics::GetPlayerController(this,0)->SetInputMode(UI);
	ResumeGame->OnClicked.AddDynamic(this,&UPauseScreen::ResumeButtonClicked);
	MainMenu->OnClicked.AddDynamic(this,&UPauseScreen::MenuButtonClicked);
	OptionsButton->OnClicked.AddDynamic(this,&UPauseScreen::OptionsButtonClicked);
}

void UPauseScreen::ResumeButtonClicked()
{
	UGameplayStatics::SetGamePaused(this, false);
	ACustomHUD* CustomHUD=Cast<ACustomHUD>(UGameplayStatics::GetPlayerController(this,0)->GetHUD());
	UGameplayStatics::GetPlayerController(this,0)->SetShowMouseCursor(false);
	UGameplayStatics::GetPlayerController(this,0)->SetInputMode(Game);
	RemoveFromParent();
	CustomHUD->UIWidget->AddToViewport(0);
}

void UPauseScreen::MenuButtonClicked()
{
	RemoveFromParent();
	UBardGameInstance* BardGameInstance=Cast<UBardGameInstance>(GetGameInstance());
	BardGameInstance->HasSpawnedMainMenu=false;
	UGameplayStatics::OpenLevel(this,"MainMenuMap");
}

void UPauseScreen::OptionsButtonClicked()
{
	ACustomHUD* CustomHUD=Cast<ACustomHUD>(UGameplayStatics::GetPlayerController(this,0)->GetHUD());
	RemoveFromParent();
	CustomHUD->SettingsScreen->AddToViewport(0);
}
