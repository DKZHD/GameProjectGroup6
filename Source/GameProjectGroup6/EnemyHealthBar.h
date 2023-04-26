// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "EnemyHealthBar.generated.h"


UCLASS()
class GAMEPROJECTGROUP6_API UEnemyHealthBar : public UUserWidget
{
	GENERATED_BODY()

public:
	//
	UPROPERTY(meta = (BindWidget))
		class UProgressBar* HealthBar;
	
};
