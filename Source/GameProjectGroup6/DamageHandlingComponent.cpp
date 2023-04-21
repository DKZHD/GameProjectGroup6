// Fill out your copyright notice in the Description page of Project Settings.


#include "DamageHandlingComponent.h"

// Sets default values for this component's properties
UDamageHandlingComponent::UDamageHandlingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	DefaultHealth = 5;
	Health = DefaultHealth;
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
}

void UDamageHandlingComponent::TakeDamage(AActor* DamagedActor, float Damage, const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser)
{
	
	Health -= Damage;
}



