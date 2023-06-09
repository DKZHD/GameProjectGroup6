// Copyright Epic Games, Inc. All Rights Reserved.

#include "GameProjectGroup6GameMode.h"
#include "CustomHUD.h"
#include "UObject/ConstructorHelpers.h"

AGameProjectGroup6GameMode::AGameProjectGroup6GameMode()
{
	// set default hud class to the custom hud created
	static ConstructorHelpers::FClassFinder<AHUD> HUDBase(TEXT("/Game/UI_Hud/BP_PlayerHUD"));
	if(HUDBase.Class != NULL)
	{
		HUDClass = HUDBase.Class;
	}
}
