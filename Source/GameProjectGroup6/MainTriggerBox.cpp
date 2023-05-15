// Fill out your copyright notice in the Description page of Project Settings.


#include "MainTriggerBox.h"

#include "Enemy.h"
#include "Engine/World.h"
#include "EntitySystem/MovieSceneEntitySystemRunner.h"
#include "Containers/UnrealString.h"
#include "BardPlayer.h"
#include "GameFramework/CharacterMovementComponent.h"


AMainTriggerBox::AMainTriggerBox()
{
	SpawnAmountStart = 3;
	SpawnAmountInGame = 3;
	
	for (int i = 0; i < SpawnAmountStart; i++)
	{
		SpawnPoints.Add(CreateDefaultSubobject<USceneComponent>(FName("StartGame_"+FString::FromInt(i+1))));
	}
	for(int i = 0; i < SpawnAmountInGame; i++)
	{
		InGameSpawnPoints.Add(CreateDefaultSubobject<USceneComponent>(FName("InGame_"+FString::FromInt(i+1))));
	}
	
}

void AMainTriggerBox::BeginPlay()
{
	Super::BeginPlay();
	OnActorBeginOverlap.AddDynamic(this, &AMainTriggerBox::OnOverlapBegin);
    	for (int i = 0 ; i < SpawnPoints.Num(); i++)
    	{
    		SpawnEnemy(SpawnPoints[i]);
    	}
}

void AMainTriggerBox::OnOverlapBegin(AActor* OverlappedActor, AActor* OtherActor)
{
	Player = Cast<ABardPlayer>(OtherActor);
	if (Enemy)
	{
		for (int i = 0 ; i < InGameSpawnPoints.Num(); i++)
		{
			SpawnEnemy(InGameSpawnPoints[i]);
		}
		for (int i = 0 ; i < AllSpawnedEnemies.Num(); i++)
		{
			AllSpawnedEnemies[i]->GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Walking);
		}
	}
	
	this->Destroy();
}

void AMainTriggerBox::SpawnEnemy(USceneComponent* SpawnPoint)
{
	Enemy = GetWorld()->SpawnActor<AEnemy>(Enemy_BP, SpawnPoint->GetComponentLocation(), FRotator::ZeroRotator);
	AllSpawnedEnemies.Add(Enemy);
}