// Fill out your copyright notice in the Description page of Project Settings.


#include "CustomHUD.h"
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
	// UGameplayStatics::GetPlayerController(GetWorld(), 0)->SetInputMode(GameOnly);
	CreateWidget<UUserWidget>(GetWorld(), UI_BP)->AddToViewport(0);
	
		
	//GetWorldTimerManager().SetTimer(Handle,this,&ACustomHUD::ClearWidgets,1,false,3.f);
}

void ACustomHUD::ClearWidgets()
{
	UWidgetLayoutLibrary::RemoveAllWidgets(this);
}

