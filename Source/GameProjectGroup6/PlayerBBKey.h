// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Object.h"
#include "PlayerBBKey.generated.h"

/**
 * 
 */
UCLASS()
class GAMEPROJECTGROUP6_API UPlayerBBKey : public UBlackboardKeyType_Object
{
	GENERATED_BODY()

	UPlayerBBKey();

protected:
	virtual void BeginPlay() override;
public:

	UPROPERTY(EditAnywhere, Category = "PlayerBBKey")
		class ABardPlayer* Player;
	
};
