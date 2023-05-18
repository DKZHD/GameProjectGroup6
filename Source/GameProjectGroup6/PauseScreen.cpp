// Fill out your copyright notice in the Description page of Project Settings.


#include "PauseScreen.h"
#include "BardGameInstance.h"
#include "BardPlayer.h"
#include "CustomHUD.h"
#include "SettingsWidget.h"
#include "UI.h"
#include "Components/Button.h"
#include "Components/Slider.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"

//Freeze game when added, also adds functionality to buttons
void UPauseScreen::NativeConstruct()
{
	Super::NativeConstruct();
	UGameplayStatics::GetPlayerController(this,0)->SetShowMouseCursor(true);
	UGameplayStatics::SetGamePaused(this, true);
	UGameplayStatics::GetPlayerController(this,0)->SetInputMode(GameUI);
	ResumeGame->OnClicked.AddDynamic(this,&UPauseScreen::ResumeButtonClicked);
	MainMenu->OnClicked.AddDynamic(this,&UPauseScreen::MenuButtonClicked);
	OptionsButton->OnClicked.AddDynamic(this,&UPauseScreen::OptionsButtonClicked);
	BardGameInstance=Cast<UBardGameInstance>(GetGameInstance());
	CustomHUD=Cast<ACustomHUD>(UGameplayStatics::GetPlayerController(this,0)->GetHUD());
	Bard = Cast<ABardPlayer>(UGameplayStatics::GetPlayerCharacter(GetWorld(),0));
}

//When Resume is clicked
void UPauseScreen::ResumeButtonClicked()
{
	Bard->IsOpen=false;
	UGameplayStatics::PlaySound2D(this,ClickSound);
	UGameplayStatics::SetGamePaused(this, false);
	UGameplayStatics::GetPlayerController(this,0)->SetShowMouseCursor(false);
	UGameplayStatics::GetPlayerController(this,0)->SetInputMode(Game);
	RemoveFromParent();
	if(!BardGameInstance->HideHUDGameInstance)
		CustomHUD->UIWidget->AddToViewport(0);
}

//When Main Menu is clicked
void UPauseScreen::MenuButtonClicked()
{
	UGameplayStatics::PlaySound2D(GetWorld(),ClickSound);
	RemoveFromParent();
	BardGameInstance->HasSpawnedMainMenu=false;
	UGameplayStatics::OpenLevel(this,"MainMenuMap");
}

//When Options is pressed
void UPauseScreen::OptionsButtonClicked()
{
	UGameplayStatics::PlaySound2D(this,ClickSound);
	CustomHUD->SettingsScreen->VolumeSlider->SetValue(BardGameInstance->VolumeLevel);
	RemoveFromParent();
	CustomHUD->SettingsScreen->AddToViewport(0);
}
