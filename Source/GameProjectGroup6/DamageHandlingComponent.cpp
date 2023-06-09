// Fill out your copyright notice in the Description page of Project Settings.


#include "DamageHandlingComponent.h"

#include "NiagaraFunctionLibrary.h"
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
//When Owner takes any amount how damage
void UDamageHandlingComponent::TakeDamage(AActor* DamagedActor, float Damage, const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser)
{
	FVector Start=GetOwner()->GetActorLocation();
	FVector End=GetOwner()->GetActorLocation()-FVector(0,0,100);
	bool LinetraceHit=GetWorld()->LineTraceSingleByChannel(Hit,Start,End,ECC_Visibility);

	// Hit.Location+FVector(0,0,1)
	if(LinetraceHit)
	UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(),Blood,GetOwner()->GetActorLocation());
	Health -= Damage;
	if (Health < 1)
	{
		IsDead = true;
	}
}
//For Enemy Health Bar
float UDamageHandlingComponent::GetHealthPercent()
{
	return Health / DefaultHealth;
}



