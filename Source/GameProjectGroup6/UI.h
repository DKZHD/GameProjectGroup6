// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UI.generated.h"

/**
 * 
 */
UCLASS()
class GAMEPROJECTGROUP6_API UUI : public UUserWidget
{
	GENERATED_BODY()

		UPROPERTY(EditAnywhere, meta = (BindWidget))
		class UProgressBar* HP_Bar;


};
