// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class TestRPG : ModuleRules
{
	public TestRPG(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] 
		{ 
			"Core", 
			"CoreUObject", 
			"Engine", 
			"InputCore", 
			"HeadMountedDisplay", 
			"EnhancedInput",
			"GameplayAbilities",
			"GameplayTags",
			"GameplayTasks", 
			"UMG"
		});

		PublicIncludePaths.AddRange(new string[] 
		{
			"TestRPG/Public/AbilitySystem/Abilities",
			"TestRPG/Public/Character",
			"TestRPG/Public/Enemy"
		});
	}
}
