// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class Lab3Character : ModuleRules
{
	public Lab3Character(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
	
		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore" });

		PrivateDependencyModuleNames.AddRange(new string[] {  });

        PublicIncludePaths.AddRange(
                new string[] {
                    "Lab3Character/",
                    "Lab3Character/Ring/",
                    "Lab3Character/Pawn/",
                    "Lab3Character/PlayerController/",
                    "Lab3Character/Spawner/",
                    "Lab3Character/PlayerState/",
                    "Lab3Character/GameState/",
                    "Lab3Character/Weapons/",
                    "Lab3Character/Character/",
                   
					// ... add public include paths required here ...
				}
                );

        // Uncomment if you are using Slate UI
        // PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });

        // Uncomment if you are using online features
        // PrivateDependencyModuleNames.Add("OnlineSubsystem");

        // To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
    }
}
