// Fill out your copyright notice in the Description page of Project Settings.


#include "MainMenu.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"
#include "CustomHUD.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Blueprint/WidgetLayoutLibrary.h"
#include "GameFramework/GameModeBase.h"

void UMainMenu::NativeConstruct()
{
	StartGame->OnClicked.AddDynamic(this, &UMainMenu::StartGameButtonClicked);
	ExitGame->OnClicked.AddDynamic(this, &UMainMenu::EndGameClicked);
}

void UMainMenu::StartGameButtonClicked()
{
	UWidgetLayoutLibrary::RemoveAllWidgets(GetWorld());
	UGameplayStatics::OpenLevel(GetWorld(), "NewMap_lvl_1",false);
}

void UMainMenu::EndGameClicked()
{
	UKismetSystemLibrary::QuitGame(GetWorld(),UGameplayStatics::GetPlayerController(GetWorld(),0),EQuitPreference::Quit,false);
}
