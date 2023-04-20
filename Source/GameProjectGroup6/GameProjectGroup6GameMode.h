// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "GameProjectGroup6GameMode.generated.h"

UCLASS(minimalapi)
class AGameProjectGroup6GameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	AGameProjectGroup6GameMode();
	UPROPERTY(EditAnywhere)
		TSubclassOf<class ACustomHUD> CustomHUD_BP;
};



