// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class Comabt : ModuleRules
{
	public Comabt(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] {
			"Core",
			"CoreUObject",
			"Engine",
			"InputCore",
			"EnhancedInput",
			"AIModule",
			"StateTreeModule",
			"GameplayStateTreeModule",
			"UMG",
			"Slate"
		});

		PrivateDependencyModuleNames.AddRange(new string[] { });

		PublicIncludePaths.AddRange(new string[] {
			"Comabt",
			"Comabt/Variant_Platforming",
			"Comabt/Variant_Platforming/Animation",
			"Comabt/Variant_Combat",
			"Comabt/Variant_Combat/AI",
			"Comabt/Variant_Combat/Animation",
			"Comabt/Variant_Combat/Gameplay",
			"Comabt/Variant_Combat/Interfaces",
			"Comabt/Variant_Combat/UI",
			"Comabt/Variant_SideScrolling",
			"Comabt/Variant_SideScrolling/AI",
			"Comabt/Variant_SideScrolling/Gameplay",
			"Comabt/Variant_SideScrolling/Interfaces",
			"Comabt/Variant_SideScrolling/UI"
		});

		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });

		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}
