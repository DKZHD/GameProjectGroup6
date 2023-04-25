// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthBardComponent.h"
#include "EnemyHealthBar.h"
#include "Components/ProgressBar.h"


void UHealthBardComponent::SetHealthPercent(float HealthPercent)
{
	if(HealthBarWidget == nullptr)
	{
		HealthBarWidget = Cast<UEnemyHealthBar>(GetUserWidgetObject());
	}
	if(HealthBarWidget && HealthBarWidget->HealthBar)
	{
		HealthBarWidget->HealthBar->SetPercent(HealthPercent);
	}
	
	
}
