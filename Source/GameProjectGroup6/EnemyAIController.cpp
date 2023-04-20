// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyAIController.h"
#include "BardPlayer.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Object.h"


AEnemyAIController::AEnemyAIController()
{
	
}

void AEnemyAIController::BeginPlay()
{
	Super::BeginPlay();
	RunBehaviorTree(BT);
	if(BlackboardComp)
	{
		BlackboardComp->SetValueAsObject("Player", GetWorld()->GetFirstPlayerController()->GetCharacter());
	}
}

void AEnemyAIController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}