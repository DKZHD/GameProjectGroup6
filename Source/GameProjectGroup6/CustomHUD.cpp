// Fill out your copyright notice in the Description page of Project Settings.


#include "CustomHUD.h"
#include "UI.h"
#include "Blueprint/UserWidget.h"

void ACustomHUD::BeginPlay()
{
	Super::BeginPlay();
	if (UUserWidget* UIClass = CreateWidget<UUserWidget>(GetWorld(), UI_BP))
		UIClass->AddToViewport(0);
}

