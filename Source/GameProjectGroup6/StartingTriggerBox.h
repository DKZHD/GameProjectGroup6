// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/TriggerBox.h"
#include "StartingTriggerBox.generated.h"

/**
 * 
 */
UCLASS()
class GAMEPROJECTGROUP6_API AStartingTriggerBox : public ATriggerBox
{
	GENERATED_BODY()

public:
	AStartingTriggerBox();
	
	UFUNCTION()
	void OnOverlapBegin(class AActor* OverlappedActor, class AActor* OtherActor);

	UFUNCTION()
	void SpawnEnemy(FVector SpawnLocation);
	
protected:
	virtual void BeginPlay() override;

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemies")
	class AEnemy* Enemy;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemies")
	TSubclassOf<AActor> Enemy_BP;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemies")
	TArray<AActor*> Enemies;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player")
	class ABardPlayer* Player;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SpawnPoints")
	FVector SpawnLocation;
};
