// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/TriggerBox.h"
#include "MainTriggerBox.generated.h"

UCLASS()
class GAMEPROJECTGROUP6_API AMainTriggerBox : public ATriggerBox
{
	GENERATED_BODY()

	protected:
	virtual void BeginPlay() override;

	public:
	AMainTriggerBox();
	
	UFUNCTION()
	void OnOverlapBegin(class AActor* OverlappedActor, class AActor* OtherActor);
	
	UFUNCTION()
	void SpawnEnemy(USceneComponent* SpawnPoint);
	
	UPROPERTY()
	class AEnemy* Enemy;

	UPROPERTY()
	class ABardPlayer* Player;

	UPROPERTY(BluePrintReadWrite, EditAnywhere, Category = "SpawnPoints")
	FRotator SpawnRotation;

	UPROPERTY(BluePrintReadWrite, EditAnywhere, Category = "SpawnPoints")
	FVector SpawnLocation;

	UPROPERTY(BluePrintReadWrite, EditAnywhere, Category = "SpawnPoints")
	TArray<USceneComponent*> SpawnPoints;

	UPROPERTY(BluePrintReadWrite, EditAnywhere, Category = "Enemies")
	TSubclassOf<AEnemy> Enemy_BP;

	UPROPERTY(BluePrintReadWrite, EditAnywhere, Category = "Enemies")
	int SpawnAmount;

	

};
