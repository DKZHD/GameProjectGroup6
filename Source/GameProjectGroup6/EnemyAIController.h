// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "EnemyAIController.generated.h"


/**
 * 
 */
class UBlackboardComponent;

UCLASS()
class GAMEPROJECTGROUP6_API AEnemyAIController : public AAIController
{
	GENERATED_BODY()
public:
	AEnemyAIController();
	
	virtual void Tick(float DeltaSeconds) override;

	virtual void OnPossess(APawn* InPawn) override;

	//Which Behaviour tree to use
	UPROPERTY(EditAnywhere)
	UBehaviorTree* BT;

	//Components for the blackboard
	UPROPERTY()
	UBlackboardComponent* BB;
	UPROPERTY(EditAnywhere)
	UBlackboardData* BBKey;
	
protected:
	virtual void BeginPlay() override;

	
};
