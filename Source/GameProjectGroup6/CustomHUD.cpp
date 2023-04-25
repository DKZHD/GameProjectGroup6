// Fill out your copyright notice in the Description page of Project Settings.


#include "CustomHUD.h"
#include "UI.h"
#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"


void ACustomHUD::BeginPlay()
{
	Super::BeginPlay();
	UGameplayStatics::GetPlayerController(GetWorld(), 0)->SetInputMode(GameOnly);
	if (UUserWidget* UIClass = CreateWidget<UUserWidget>(GetWorld(), UI_BP))
		UIClass->AddToViewport(0);
	
}

