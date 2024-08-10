// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class KeyboardSimulator : ModuleRules
{
	public KeyboardSimulator(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput", "CableComponent" });
 PrivateIncludePathModuleNames.AddRange(new string[] { "CableComponent" });
	}
}
