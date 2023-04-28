// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class GameProjectGroup6 : ModuleRules
{
	public GameProjectGroup6(ReadOnlyTargetRules Target) : base(Target)
	{
		PrivateDependencyModuleNames.AddRange(new string[] { "GameplayCameras" });
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay", "EnhancedInput", "UMG", "Niagara","SlateCore" });
	}
}
