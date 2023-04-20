// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "EnemyAIController.generated.h"

/**
 * 
 */
UCLASS()
class GAMEPROJECTGROUP6_API AEnemyAIController : public AAIController
{
	GENERATED_BODY()
public:
	AEnemyAIController();
	virual void Tick(float DeltaSeconds) override;
	
	UPROPERTY(EditAnywhere)
		UBehaviorTree* BT;
protected:
	virtual void BeginPlay() override;
};
