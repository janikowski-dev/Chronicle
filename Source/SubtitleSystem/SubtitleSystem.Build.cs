using UnrealBuildTool;

public class SubtitleSystem : ModuleRules
{
	public SubtitleSystem(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
		
		PublicDependencyModuleNames.AddRange([
			"Core",
			"CoreUObject",
			"Engine",
			"UMG",
			"Slate",
			"SlateCore",
			"DeveloperSettings"
		]);

		PrivateDependencyModuleNames.AddRange([
		]);
	}
}
