// Fill out your copyright notice in the Description page of Project Settings.


#include "StartingTriggerBox.h"

#include "BardPlayer.h"
#include "Kismet/GameplayStatics.h"
#include "Enemy.h"
#include "GameFramework/CharacterMovementComponent.h"

AStartingTriggerBox::AStartingTriggerBox()
{
}

void AStartingTriggerBox::BeginPlay()
{
	Super::BeginPlay();
	OnActorBeginOverlap.AddDynamic(this, &AStartingTriggerBox::OnOverlapBegin);

	SpawnLocation = FVector(320.f, -2580.f, 98.f);

	SpawnEnemy(SpawnLocation);
}

void AStartingTriggerBox::OnOverlapBegin(AActor* OverlappedActor, AActor* OtherActor)
{
	Player = Cast<ABardPlayer>(OtherActor);
	if(Enemy)
	{
		Enemy->GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Walking);
	}
	this->Destroy();
}

void AStartingTriggerBox::SpawnEnemy(FVector Spawn)
{
	Enemy = GetWorld()->SpawnActor<AEnemy>(Enemy_BP, Spawn, FRotator::ZeroRotator);
	Enemy->GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_None);
}