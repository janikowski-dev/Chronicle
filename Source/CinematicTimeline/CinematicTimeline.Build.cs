using UnrealBuildTool;

public class CinematicTimeline : ModuleRules
{
	public CinematicTimeline(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
		
		PublicDependencyModuleNames.AddRange([
			"Core",
			"CoreUObject",
			"Engine"
		]);
		
		PrivateDependencyModuleNames.AddRange([
			"ChronicleCore",
			"CharacterSystem",
			"SubtitleSystem",
			"LevelSequence",
			"MovieScene",
			"MovieSceneTracks",
			"CinematicCamera"
		]);
	}
}