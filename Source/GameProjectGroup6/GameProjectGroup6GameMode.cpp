// Copyright Epic Games, Inc. All Rights Reserved.

#include "GameProjectGroup6GameMode.h"
#include "GameProjectGroup6Character.h"
#include "UObject/ConstructorHelpers.h"

AGameProjectGroup6GameMode::AGameProjectGroup6GameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
