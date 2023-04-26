// Fill out your copyright notice in the Description page of Project Settings.


#include "CustomHUD.h"

#include "BardGameInstance.h"
#include "MainMenu.h"
#include "UI.h"
#include "Blueprint/UserWidget.h"
#include "Blueprint/WidgetLayoutLibrary.h"
#include "Kismet/GameplayStatics.h"


ACustomHUD::ACustomHUD()
{
	
}

void ACustomHUD::BeginPlay()
{
	Super::BeginPlay();
	MenuWidget=CreateWidget<UUserWidget>(GetWorld(), MainMenu_BP);
	UIWidget=CreateWidget<UUserWidget>(GetWorld(), UI_BP);
	BardGameInstance=Cast<UBardGameInstance>(GetGameInstance());
	if(!BardGameInstance->HasSpawnedMainMenu)
	{
		if(MenuWidget)
		MenuWidget->AddToViewport(0);
		BardGameInstance->HasSpawnedMainMenu=true;
	}
	else
	{
		ClearWidgets();
		if(UIWidget)
		{
			UIWidget->AddToViewport(0);
		}
	}

}

void ACustomHUD::ClearWidgets()
{
	UWidgetLayoutLibrary::RemoveAllWidgets(this);
}

