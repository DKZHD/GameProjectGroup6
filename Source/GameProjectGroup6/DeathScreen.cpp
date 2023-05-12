// Fill out your copyright notice in the Description page of Project Settings.


#include "DeathScreen.h"

#include "BardGameInstance.h"
#include "Blueprint/WidgetLayoutLibrary.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"

//Called when Widget is created
void UDeathScreen::NativeConstruct()
{
	APlayerController* PC=Cast<APlayerController>(UGameplayStatics::GetPlayerController(this,0));
	PC->SetShowMouseCursor(true);
	UGameplayStatics::SetGamePaused(this,true);
	PC->SetInputMode(UIOnly);
	Retry->OnClicked.AddDynamic(this, &UDeathScreen::RetryFunction);
	Menu->OnClicked.AddDynamic(this, &UDeathScreen::MenuFunction);
	Quit->OnClicked.AddDynamic(this, &UDeathScreen::QuitFunction);
}

//When Retry button is clicked
void UDeathScreen::RetryFunction()
{
	APlayerController* PC=Cast<APlayerController>(UGameplayStatics::GetPlayerController(this,0));
	PC->SetShowMouseCursor(false);
	UGameplayStatics::SetGamePaused(this,false);
	PC->SetInputMode(Game);
	UWidgetLayoutLibrary::RemoveAllWidgets(GetWorld());
	UGameplayStatics::OpenLevel(GetWorld(), "NewMap_lvl_1");
}

//When Main menu button is clicked
void UDeathScreen::MenuFunction()
{
	UBardGameInstance* BardGameInstance=Cast<UBardGameInstance>(GetGameInstance());
	BardGameInstance->HasSpawnedMainMenu=false;
	UGameplayStatics::OpenLevel(this,"MainMenuMap");
	RemoveFromParent();
}

//When Quit button is clicked
void UDeathScreen::QuitFunction()
{
	UKismetSystemLibrary::QuitGame(GetWorld(),UGameplayStatics::GetPlayerController(GetWorld(),0),EQuitPreference::Quit,false);
}
