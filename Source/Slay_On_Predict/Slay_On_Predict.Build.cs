// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class Slay_On_Predict : ModuleRules
{
	public Slay_On_Predict(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay","UMG" });
	}
}
