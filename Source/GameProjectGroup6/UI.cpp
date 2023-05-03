// Fill out your copyright notice in the Description page of Project Settings.


#include "UI.h"

#include "BardPlayer.h"
#include "DamageHandlingComponent.h"
#include "Kismet/GameplayStatics.h"

void UUI::NativeConstruct()
{
	Bard = Cast<ABardPlayer>(UGameplayStatics::GetPlayerCharacter(GetWorld(),0));
}

float UUI::GetHealthPercent()
{
if(Bard)
{
	float Current = Bard->DamageHandlingComponent->Health;
	float Default = Bard->DamageHandlingComponent->DefaultHealth;                                                          	
    FMath::Clamp(Health = Current / Default,0,1);
}

	

	if (Health >= 1)
	{
		return 1.f;
	}
	if (Health <= .81&&Health>.61)
	{
		return 0.7;
	}
	if (Health <= .61 && Health>.41)
	{
		return 0.595;
	}
	
	if (Health <= .41 && Health>.21)
	{
		return 0.5;
	}
	if (Health <= .21 && Health>0)
	{
		return 0.4;
	}
	if (Health <= 0)
	{
		return 0.f;
	}
	return 0;

}

