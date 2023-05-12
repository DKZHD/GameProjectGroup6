// Fill out your copyright notice in the Description page of Project Settings.


#include "MainMenu.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"
#include "CustomHUD.h"
#include "SettingsWidget.h"
#include "Blueprint/WidgetLayoutLibrary.h"

//Bind Click functionality 
void UMainMenu::NativeConstruct()
{
	StartGame->OnClicked.AddDynamic(this, &UMainMenu::StartGameButtonClicked);
	Settings->OnClicked.AddDynamic(this,&UMainMenu::SettingsButton);
	ExitGame->OnClicked.AddDynamic(this, &UMainMenu::EndGameClicked);
}

//When Start Game is clicked
void UMainMenu::StartGameButtonClicked()
{
	UWidgetLayoutLibrary::RemoveAllWidgets(GetWorld());
	UGameplayStatics::GetPlayerCameraManager(this,0)->StartCameraFade(0,1,2,FLinearColor::Black);
	UGameplayStatics::OpenLevel(GetWorld(), "NewMap_lvl_1",true);
}

//When Settings is clicked
void UMainMenu::SettingsButton()
{
	ACustomHUD* CustomHUD=Cast<ACustomHUD>(UGameplayStatics::GetPlayerController(this,0)->GetHUD());
	CustomHUD->MenuWidget->RemoveFromParent();
	OpenedFromMenu=true;
	CustomHUD->SettingsScreen->AddToViewport(0);
}

//When End game is clicked
void UMainMenu::EndGameClicked()
{
	UKismetSystemLibrary::QuitGame(GetWorld(),UGameplayStatics::GetPlayerController(GetWorld(),0),EQuitPreference::Quit,false);
}
