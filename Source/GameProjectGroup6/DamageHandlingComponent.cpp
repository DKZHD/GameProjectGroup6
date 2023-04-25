// Fill out your copyright notice in the Description page of Project Settings.


#include "DamageHandlingComponent.h"

#include "Engine/Engine.h"

// Sets default values for this component's properties
UDamageHandlingComponent::UDamageHandlingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;
	DefaultHealth = 5;
	
}


// Called when the game starts
void UDamageHandlingComponent::BeginPlay()
{
	Super::BeginPlay();
	AActor* Owner = GetOwner();
	if(Owner)
	{
		Owner->OnTakeAnyDamage.AddDynamic(this,&UDamageHandlingComponent::TakeDamage);
	}
	Health = DefaultHealth;
}

void UDamageHandlingComponent::TakeDamage(AActor* DamagedActor, float Damage, const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser)
{
	Health -= Damage;
	if (Health < 1)
		GEngine->AddOnScreenDebugMessage(0, 2.f, FColor::Red, "Dead");
}



