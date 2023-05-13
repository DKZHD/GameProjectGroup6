// Fill out your copyright notice in the Description page of Project Settings.


#include "MainTriggerBox.h"

#include "Enemy.h"
#include "Engine/World.h"
#include "EntitySystem/MovieSceneEntitySystemRunner.h"
#include "Containers/UnrealString.h"
#include "BardPlayer.h"


AMainTriggerBox::AMainTriggerBox()
{
	SpawnAmount = 3;

	for (int i = 0; i < SpawnAmount; i++)
	{
		SpawnPoints.Add(CreateDefaultSubobject<USceneComponent>(FName(FString::FromInt(i))));
	}
}

void AMainTriggerBox::BeginPlay()
{
	Super::BeginPlay();
	OnActorBeginOverlap.AddDynamic(this, &AMainTriggerBox::OnOverlapBegin);

	SpawnLocation = FVector(960.0, -4570.f, 114.f);
}

void AMainTriggerBox::OnOverlapBegin(AActor* OverlappedActor, AActor* OtherActor)
{
    GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Overlap Begin"));
	Player = Cast<ABardPlayer>(OtherActor);
	for (int i = 0; i < SpawnAmount; i++)
       	{
       	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Spawn Enemy"));
		SpawnEnemy(SpawnPoints[i]);
       	}
	this->Destroy();
}

void AMainTriggerBox::SpawnEnemy(USceneComponent* SpawnPoint)
{
	Enemy = GetWorld()->SpawnActor<AEnemy>(Enemy_BP, SpawnPoint->GetComponentLocation(), FRotator::ZeroRotator);

}