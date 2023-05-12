// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyAIController.h"
#include "BardPlayer.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"


AEnemyAIController::AEnemyAIController()
{

}
void AEnemyAIController::BeginPlay()
{
	Super::BeginPlay();
	ABardPlayer* Bard = Cast<ABardPlayer>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	RunBehaviorTree(BT);
	UseBlackboard(BBKey, BB);
	
	//Make Ai know who the player is
	if(Bard)
	BB->SetValueAsObject(FName("Player"), Bard);
}

void AEnemyAIController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}