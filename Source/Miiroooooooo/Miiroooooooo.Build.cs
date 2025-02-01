// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class Miiroooooooo : ModuleRules
{
	public Miiroooooooo(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput" });

		PublicIncludePaths.AddRange(new string[]
		{
            "Miiroooooooo/Public/Character",
            "Miiroooooooo/Public/Component",
            "Miiroooooooo/Public/Controller",
            "Miiroooooooo/Public/GameMode",
			"Miiroooooooo/Public/Items",
            "Miiroooooooo/Public/Items/UsableItems",
            "Miiroooooooo/Public/Items/EquipmentItems",
            "Miiroooooooo/Public/Maze",
			"Miiroooooooo/Public/Widget"        
        });
	}
}
