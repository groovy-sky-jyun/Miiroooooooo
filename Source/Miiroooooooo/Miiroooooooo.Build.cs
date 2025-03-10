// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class Miiroooooooo : ModuleRules
{
	public Miiroooooooo(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput", "EnhancedInput" });

		PublicIncludePaths.AddRange(new string[]
		{
            "Miiroooooooo/Public/Character",
            "Miiroooooooo/Public/Component",
            "Miiroooooooo/Public/Controller",
            "Miiroooooooo/Public/GameMode",
            "Miiroooooooo/Public/GameInstance",
            "Miiroooooooo/Public/Items",
            "Miiroooooooo/Public/Items/UsableItems",
            "Miiroooooooo/Public/Maze",
            "Miiroooooooo/Public/Trap",
            "Miiroooooooo/Public/Structure",
            "Miiroooooooo/Public/Widget"        
        });
	}
}
