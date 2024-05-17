// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class ShaderProgramModule : ModuleRules
{
	public ShaderProgramModule(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
	
		PublicDependencyModuleNames .AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput", "RHI", "RenderCore" });

		PrivateDependencyModuleNames.AddRange(new string[] { "Projects" });
	}
}
