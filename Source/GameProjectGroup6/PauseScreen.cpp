// Fill out your copyright notice in the Description page of Project Settings.


#include "PauseScreen.h"

#include "BardGameInstance.h"
#include "CustomHUD.h"
#include "SettingsWidget.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"

//Freeze game when added, also adds functionality to buttons
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

//When Resume is clicked
void UPauseScreen::ResumeButtonClicked()
{
	UGameplayStatics::PlaySound2D(this,ClickSound);
	UGameplayStatics::SetGamePaused(this, false);
	ACustomHUD* CustomHUD=Cast<ACustomHUD>(UGameplayStatics::GetPlayerController(this,0)->GetHUD());
	UGameplayStatics::GetPlayerController(this,0)->SetShowMouseCursor(false);
	UGameplayStatics::GetPlayerController(this,0)->SetInputMode(Game);
	RemoveFromParent();
	CustomHUD->UIWidget->AddToViewport(0);
}

//When Main Menu is clicked
void UPauseScreen::MenuButtonClicked()
{
	UGameplayStatics::PlaySound2D(GetWorld(),ClickSound);
	UBardGameInstance* BardGameInstance=Cast<UBardGameInstance>(GetGameInstance());
	RemoveFromParent();
	BardGameInstance->HasSpawnedMainMenu=false;
	UGameplayStatics::OpenLevel(this,"MainMenuMap");
}

//When Options is pressed
void UPauseScreen::OptionsButtonClicked()
{
	UGameplayStatics::PlaySound2D(this,ClickSound);
	ACustomHUD* CustomHUD=Cast<ACustomHUD>(UGameplayStatics::GetPlayerController(this,0)->GetHUD());
	RemoveFromParent();
	CustomHUD->SettingsScreen->AddToViewport(0);
}
