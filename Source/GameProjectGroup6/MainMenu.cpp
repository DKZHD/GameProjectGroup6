// Fill out your copyright notice in the Description page of Project Settings.


#include "MainMenu.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"

void UMainMenu::NativeConstruct()
{
	StartGame->OnClicked.AddDynamic(this, &UMainMenu::StartGameButtonClicked);
}

void UMainMenu::StartGameButtonClicked()
{
	UGameplayStatics::OpenLevel(GetWorld(), "NewMap_lvl_1", true);
	
}
