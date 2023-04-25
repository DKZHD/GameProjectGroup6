// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/WidgetComponent.h"
#include "HealthBardComponent.generated.h"

UCLASS()
class GAMEPROJECTGROUP6_API UHealthBardComponent : public UWidgetComponent
{
	GENERATED_BODY()

public:
	void SetHealthPercent(float HealthPercent);

private:
	class UEnemyHealthBar* HealthBarWidget;
};
